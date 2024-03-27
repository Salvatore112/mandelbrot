#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <GL/freeglut.h>

#ifndef _WIN32
#include <unistd.h>
#define sleep(x) usleep((x) * 1000)
#else
#define popen(x, y) _popen((x), (y))
#define sleep(x) Sleep(x)
#endif

#define LIMIT(x, min, max) ((x) > (max) ? (max) : (x) < (min) ? (min) \
: (x))
#define MAX(x, min) ((x) < (min) ? (min) : (x))
#define MIN(x, max) ((x) > (max) ? (max) : (x))

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} rgb;

typedef struct
{
    double r;
    double i;
} complex;

complex *cstore;
double *istore;
rgb *tex;

int w;
int h;

complex center = {0, 0};
double scale = 4;

complex pointer = {0, 0};
GLuint gltex;
int iter;

double er = 3.0;
double eg = 0.75;
double eb = 0.5;
int startiter = -4;
int enditer = 77;
int maxiter = 8192;

int lastchange = 0;
int redrawflag = 0;
int reshapeNeeded = 0;
int mpress = 0;
int mpressx1, mpressy1, mpressx2, mpressy2;
int iterperframe = 16;

int working = 0;
int line = -1;
pthread_mutex_t mline = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mworking = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mredraw = PTHREAD_MUTEX_INITIALIZER;

FILE *renderpipe;
char renderstate[256] = "";

complex f(complex x, complex c, double *sqr)
{
    complex res;
    double r2 = x.r * x.r;
    double i2 = x.i * x.i;
    res.r = r2 - i2 + c.r;
    res.i = 2 * x.r * x.i + c.i;
    *sqr = r2 + i2;
    return res;
}

rgb color(double iter)
{
    rgb res;
    double r, g, b, c;

    c = (iter - startiter) / (enditer - startiter);
    r = pow(c, er);
    g = pow(c, eg);
    b = pow(c, eb);

    res.r = (unsigned char)(LIMIT(r, 0.0, 1.0) * 255);
    res.g = (unsigned char)(LIMIT(g, 0.0, 1.0) * 255);
    res.b = (unsigned char)(LIMIT(b, 0.0, 1.0) * 255);

    return res;
}

void clear(void)
{
    pthread_mutex_lock(&mredraw);
    memset(cstore, 0, sizeof(complex) * w * h);
    memset(istore, 0, sizeof(double) * w * h);
    memset(tex, 0, sizeof(rgb) * w * h);
    iter = 0;
    iterperframe = 16;
    pthread_mutex_unlock(&mredraw);
}

void renderline(int y)
{
    int x;
    int index = y * w;
    for (x = 0; x < w; x++)
    {
        pthread_mutex_lock(&mredraw);
        if (istore[index] < 1e-23)
        {
            pthread_mutex_unlock(&mredraw);
            int localiter = 0;
            complex c = center;
            c.r += (x - w / 2) * scale / h;
            c.i += (y - h / 2) * scale / h;
            while (istore[index] < 1e-23 && localiter < iterperframe)
            {
                double sqr;
                cstore[index] = f(cstore[index], c, &sqr);
                if (sqr >= 1e10)
                {
                    double diter = iter + localiter - log(log(sqr) / log(1e10)) / log(2);
                    diter = MAX(diter, 1.01e-23);
                    pthread_mutex_lock(&mredraw);
                    istore[index] = diter;
                    tex[index] = color(istore[index]);
                    pthread_mutex_unlock(&mredraw);
                }
                localiter++;
            }
        }
        else
        {
            pthread_mutex_unlock(&mredraw);
        }
        index++;
    }
}

void *trender(void *a)
{
    for (;;)
    {
        sleep(1);
        pthread_mutex_lock(&mline);
        if (line < 0 || line >= h)
        {
            pthread_mutex_unlock(&mline);
            continue;
        }
        else
        {
            pthread_mutex_lock(&mworking);
            working++;
            pthread_mutex_unlock(&mworking);
            for (;;)
            {
                int thisline = line;
                if (line < 0 || line >= h)
                {
                    pthread_mutex_unlock(&mline);
                    break;
                }
                line++;
                pthread_mutex_unlock(&mline);
                renderline(thisline);
                pthread_mutex_lock(&mline);
            }
        }
        pthread_mutex_lock(&mworking);
        working--;
        pthread_mutex_unlock(&mworking);
    }
}

void idle(void)
{
    if (reshapeNeeded)
    {
        reshapeNeeded = 0;
        glutReshapeWindow(w, h);
        return;
    }

    if (iter < maxiter)
    {
        int t1, t2;

        t1 = glutGet(GLUT_ELAPSED_TIME);

        line = 0;

        while (line < h || working)
        {
            sched_yield();
        }

        line = -1;

        iter += iterperframe;

        t2 = glutGet(GLUT_ELAPSED_TIME);
        if (t2 < t1 + 20)
        {
            iterperframe += MAX(1, iterperframe / 10);
        }
        else if (t2 > t1 + 35 && iterperframe > 16)
        {
            iterperframe -= MAX(1, iterperframe / 10);
        }
    }
    glutPostRedisplay();
}

void redraw(void)
{
    int x, y;
    int index = 0;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            index++;
            if (istore[index])
            {
                tex[index] = color(istore[index]);
            }
        }
    }
    glutPostRedisplay();
}

void autoColor(void)
{
    int x, y;
    int index = 0;
    int *numpix;
    int lowest = maxiter;

    numpix = malloc(maxiter * sizeof(int));
    memset

            (numpix, 0, maxiter * sizeof(int));
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            index++;
            pthread_mutex_lock(&mline);
            numpix[LIMIT((int)istore[index], 0, maxiter - 1)]++;
            if (istore[index] > 1.02e-23)
            {
                lowest = MIN(lowest, (int)istore[index]);
            }
            pthread_mutex_unlock(&mline);
        }
    }
    x = 0;
    y = h * w / 500; // 0.2 % white pixels allowed
    for (index = maxiter - 1; index >= 0; --index)
    {
        x += numpix[index];
        if (x > y)
        {
            enditer = index;
            break;
        }
    }
    if (lowest != maxiter)
    {
        double c = 0.05;
        startiter = (int)((lowest - c * enditer) / (1.0 - c));
    }
    redraw();
}

void *pipereader(void *a)
{
    for (;;)
    {
        pthread_mutex_lock(&mworking);
        if (renderpipe)
        {
            if (!fgets(renderstate, 255, renderpipe))
            {
                fclose(renderpipe);
                renderpipe = NULL;
            }
        }
        else
        {
            sleep(1); // Sleep for 1 second
        }
        pthread_mutex_unlock(&mworking);
    }
    return NULL;
}

void drawFps(void)
{
    static int timeOld;
    static int frameCounter;
    static double dfps;

    int time;
    char buffer[16];

    frameCounter++;
    time = glutGet(GLUT_ELAPSED_TIME);

    if (time > timeOld + 500)
    {
        dfps = frameCounter * 1000.0 / (time - timeOld);

        frameCounter = 0;
        timeOld = time;
    }

    glRasterPos2i(10, 20);
    sprintf(buffer, "%.1lf fps", dfps);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);
}

void drawIter(void)
{
    char buffer[64];
    glRasterPos2i(10, 35);
    sprintf(buffer, "%d", iter);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, 50);
    sprintf(buffer, "er %lf", er);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, 65);
    sprintf(buffer, "eg %lf", eg);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, 80);
    sprintf(buffer, "eb %lf", eb);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, 95);
    sprintf(buffer, "si %d", startiter);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, 110);
    sprintf(buffer, "ei %d", enditer);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, 125);
    sprintf(buffer, "maxi %d", maxiter);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, 140);
    sprintf(buffer, "pf %d", iterperframe);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    if (renderpipe)
    {
        glRasterPos2i(10, h - 50);
        glutBitmapString(GLUT_BITMAP_9_BY_15, renderstate);
    }

    glRasterPos2i(10, h - 35);
    snprintf(buffer, 64, "height %.16lf (zoom %.2le)", scale, 1.0 / scale);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, h - 20);
    snprintf(buffer, 64, "center %.16lf + i * %.16lf", center.r, center.i);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, h - 5);
    snprintf(buffer, 64, "pointer %.16lf + i * %.16lf", pointer.r, pointer.i);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);
}

void draw(void)
{
    if (redrawflag && glutGet(GLUT_ELAPSED_TIME) - lastchange > 500)
    {
        redraw();
        redrawflag = 0;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    pthread_mutex_lock(&mworking);
    glBindTexture(GL_TEXTURE_2D, gltex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0, 0);
    glVertex2d(0, 0);
    glTexCoord2d(1, 0);
    glVertex2d(w, 0);
    glTexCoord2d(0, 1);
    glVertex2d(0, h);
    glTexCoord2d(1, 1);
    glVertex2d(w, h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    pthread_mutex_unlock(&mworking);

    if (mpress)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(mpressx1, mpressy1);
        glVertex2d(mpressx1, mpressy2);
        glVertex2d(mpressx2, mpressy2);
        glVertex2d(mpressx2, mpressy1);
        glEnd();
    }

    drawFps();
    drawIter();

    glutSwapBuffers();
}

void render(void)
{
    if (!renderpipe)
    {
        char buffer[512];
        renderstate[0] = 0;
#ifdef _WIN32
        snprintf(buffer, 512, "mandelbrot_render.exe 12 %d %d %.16lf %.16lf %.16lf %d %d %d %lf %lf %lf", w * 8, h * 8, center.r, center.i, scale, startiter, enditer, maxiter, er, eg, eb);
#else
        snprintf(buffer, 512, "./mandelbrot_render 12 %d %d %.16lf %.16lf %.16lf %d %d %d %lf %lf %lf", w * 8, h * 8, center.r, center.i, scale, startiter, enditer, maxiter, er, eg, eb);
#endif
        pthread_mutex_lock(&mworking);
        renderpipe = popen(buffer, "r");
        pthread_mutex_unlock(&mworking);
    }
}

void keyboard(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 'a':
            autoColor();
            break;
        case 'r':
            render();
            break;
        case 'R':
            clear();
            render();
            break;
        case 27:
            if (renderpipe)
            {
                pthread_mutex_lock(&mworking);
                fclose(renderpipe);
                renderpipe = NULL;
                pthread_mutex_unlock(&mworking);
            }
            else
            {
                exit(0);
            }
            break;
    }
}

void motion(int x, int y)
{
    pointer.r = (double)(x - w / 2) * scale / h;
    pointer.i = (double)(y - h / 2) * scale / h;
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mpress = 1;
            mpressx1 = x;
            mpressy1 = h - y;
        }
        else
        {
            mpress = 0;
            mpressx2 = x;
            mpressy2 = h - y;
            if (mpressx1 != mpressx2 && mpressy1 != mpressy2)
            {
                double x1 = center.r + (double)mpressx1 * scale / h;
                double x2 = center.r + (double)mpressx2 * scale / h;
                double y1 = center.i + (double)mpressy1 * scale / h;
                double y2 = center.i + (double)mpressy2 * scale / h;
                center.r = (x1 + x2) / 2;
                center.i = (y1 + y2) / 2;
                scale = MAX(fabs((x2 - x1) / 2), fabs((y2 - y1) / 2));
                render();
            }
        }
    }
}

void reshape(int width, int height)
{
    w = width;
    h = height;

    pthread_mutex_lock(&mredraw);
    free(tex);
    free(cstore);
    free(istore);
    tex = malloc(sizeof(rgb) * w * h);
    cstore = malloc(sizeof(complex) * w * h);
    istore = malloc(sizeof(double) * w * h);
    pthread_mutex_unlock(&mredraw);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    redraw();
}

int main(int argc, char **argv)
{
    int tid1, tid2;
    int i;

    w = 800;
    h = 600;

    tex = malloc(sizeof(rgb) * w * h);
    cstore = malloc(sizeof(complex) * w * h);
    istore = malloc(sizeof(double) * w * h);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(w, h);
    glutCreateWindow("Mandelbrot");

    pthread_create(&tid1, NULL, trender, NULL);
    pthread_create(&tid2, NULL, pipereader, NULL);

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}

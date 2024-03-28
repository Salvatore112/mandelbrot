#include <quadmath.h>

#include <unistd.h>
#define sleep(x) usleep((x)*1000)

#define LIMIT(x, min, max) ((x) > (max) ? (max) : (x) < (min) ? (min) : (x))
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
    __float128 r;
    __float128 i;
} complex;

complex * cstore;
double * istore;
rgb * tex;

int w;
int h;
@@ -61,604 +62,643 @@ int line = -1;
pthread_mutex_t mline;
pthread_mutex_t mworking;

FILE* renderpipe;
char renderstate[256] = "";

complex f(complex x, complex c, __float128 *sqr)
{
    // complex numbers: x * x + c;
    complex res;
    __float128 r2 = x.r * x.r;
    __float128 i2 = x.i * x.i;
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
    memset(cstore, 0, sizeof(complex) * w * h);
    memset(istore, 0, sizeof(double)  * w * h);
    memset(tex,    0, sizeof(rgb)     * w * h);
    iter = 0;
    iterperframe = 16;
}

void renderline(int y)
{
    int x;
    int index = y * w;
    for(x = 0; x < w; x++)
    {
        if(istore[index] < 1e-23)
        {
            int localiter = 0;
            complex c = center;
            c.r += (x - w / 2) * scale / h;
            c.i += (y - h / 2) * scale / h;
            while(istore[index] < 1e-23 && localiter < iterperframe)
            {
                __float128 sqr;
                cstore[index] = f(cstore[index], c, &sqr);
                if(sqr >= 1e10)
                {
                    double diter = iter + localiter - log( log(sqr) / log(1e10) ) / log(2);
                    diter = MAX(diter, 1.01e-23);
                    istore[index] = diter;
                    tex[index] = color(istore[index]);
                }
                localiter++;
            }
        }
        index++;
    }
}

void * trender(void * a)
{
    for(;;)
    {
        sleep(1);
        pthread_mutex_lock(&mline);
        if(line < 0 || line >= h)
        {
            pthread_mutex_unlock(&mline);
            continue;
        }
        else
        {
            pthread_mutex_lock(&mworking);
            working++;
            pthread_mutex_unlock(&mworking);
            for(;;)
            {
                int thisline = line;
                if(line < 0 || line >= h)
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
    if(reshapeNeeded)
    {
        reshapeNeeded = 0;
        glutReshapeWindow(w, h);
        return;
    }

    if(iter < maxiter)
    {
        int t1, t2;

        t1 = glutGet(GLUT_ELAPSED_TIME);

        line = 0;

        while(line < h || working)
        {
            sched_yield();
        }

        line = -1;

        iter += iterperframe;

        t2 = glutGet(GLUT_ELAPSED_TIME);
        if(t2 < t1 + 20)
        {
            iterperframe += MAX(1, iterperframe / 10);
        }
        else if(t2 > t1 + 35 && iterperframe > 16)
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
    for(y = 0; y < h; y++)
    {
        for(x = 0; x < w; x++)
        {
            index++;
            if(istore[index])
            {
                tex[index] = color(istore[index]);
            }
        }
    }
    glutPostRedisplay();
}

void autoColor(void)
{
    int  x, y;
    int  index = 0;
    int* numpix;
    int  lowest = maxiter;

    numpix = malloc(maxiter * sizeof(int));
    memset(numpix, 0, maxiter * sizeof(int));
    for(y = 0; y < h; y++)
    {
        for(x = 0; x < w; x++)
        {
            index++;
            numpix[LIMIT((int)istore[index],0,maxiter-1)]++;
            if(istore[index] > 1.02e-23)
            {
                lowest = MIN(lowest, (int)istore[index]);
            }
        }
    }
    x = 0;
    y = h * w / 500; // 0.2 % white pixels allowed
    for(index = maxiter - 1; index >= 0; --index)
    {
        x += numpix[index];
        if(x > y)
        {
            enditer = index;
            break;
        }
    }
    if(lowest != maxiter)
    {
        double c = 0.05;
        startiter = (int)((lowest - c * enditer) / (1.0 - c));
    }
    redraw();
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

    if(time > timeOld + 500)
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
    char buffer[128];
    int index, len;

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

    if(renderpipe)
    {
        glRasterPos2i(10, h - 50);
        glutBitmapString(GLUT_BITMAP_9_BY_15, renderstate);
    }

    glRasterPos2i(10, h - 35);
    index = len = 0;
    len = snprintf(buffer, 128, "height ");
    if(len >=0 && (index += len) < 128) len = quadmath_snprintf(buffer + index, 128 - index, "%.36Qf", scale);
    if(len >=0 && (index += len) < 128) len = snprintf(buffer + index, 512 - index, " (zoom ");
    if(len >=0 && (index += len) < 128) len = quadmath_snprintf(buffer + index, 128 - index, "%.2Qe", 1.0 / scale);
    if(len >=0 && (index += len) < 128) len = snprintf(buffer + index, 512 - index, ")");
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, h - 20);
    index = len = 0;
    len = snprintf(buffer, 128, "center ");
    if(len >=0 && (index += len) < 128) len = quadmath_snprintf(buffer + index, 128 - index, "%.36Qf", center.r);
    if(len >=0 && (index += len) < 128) len = snprintf(buffer + index, 512 - index, " + i * ");
    if(len >=0 && (index += len) < 128) len = quadmath_snprintf(buffer + index, 128 - index, "%.36Qf", center.i);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

    glRasterPos2i(10, h - 5);
    index = len = 0;
    len = snprintf(buffer, 128, "pointer ");
    if(len >=0 && (index += len) < 128) len = quadmath_snprintf(buffer + index, 128 - index, "%.36Qf", pointer.r);
    if(len >=0 && (index += len) < 128) len = snprintf(buffer + index, 512 - index, " + i * ");
    if(len >=0 && (index += len) < 128) len = quadmath_snprintf(buffer + index, 128 - index, "%.36Qf", pointer.i);
    glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);
}

void draw(void)
{
    if(redrawflag && glutGet(GLUT_ELAPSED_TIME) - lastchange > 500)
    {
        redraw();
        redrawflag = 0;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gltex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0,0);
    glVertex2d(0,0);
    glTexCoord2d(1,0);
    glVertex2d(w,0);
    glTexCoord2d(0,1);
    glVertex2d(0,h);
    glTexCoord2d(1,1);
    glVertex2d(w,h);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    if(mpress)
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

void* pipereader(void* a)
{
    for(;;)
    {
        if(renderpipe)
        {
            if(!fgets(renderstate, 255, renderpipe))
            {
                fclose(renderpipe);
                renderpipe = NULL;
            }
        }
        else
        {
            sleep(100);
        }
    }
}

void render(void)
{
    if(!renderpipe)
    {
        char buffer[512];
        int index, len;
        renderstate[0] = 0;

        index = 0;
        len = snprintf(buffer, 512, "./mandelbrot_render-f128 12 %d %d ", w * 8, h * 8);
        if(len >=0 && (index += len) < 512) len = quadmath_snprintf(buffer + index, 512 - index, "%.36Qf", center.r);
        if(len >=0 && (index += len) < 512) len = quadmath_snprintf(buffer + index, 512 - index, "%.36Qf", center.i);
        if(len >=0 && (index += len) < 512) len = quadmath_snprintf(buffer + index, 512 - index, "%.36Qf", scale);
        if(len >=0 && (index += len) < 512) snprintf(buffer + index, 512 - index, "%d %d %d %lf %lf %lf", startiter, enditer, maxiter, er, eg, eb);
        renderpipe = popen(buffer, "r");
    }
}

static void key(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            glutLeaveMainLoop();
            break;
        case 'f':
            autoColor();
            break;
        case 'q':
            er += 0.01;
            break;
        case 'a':
            er -= 0.01;
            break;
        case 'w':
            eg += 0.01;
            break;
        case 's':
            eg -= 0.01;
            break;
        case 'e':
            eb += 0.01;
            break;
        case 'd':
            eb -= 0.01;
            break;
        case 't':
            startiter += 1;
            break;
        case 'g':
            startiter -= 1;
            break;
        case 'T':
            startiter += 10;
            break;
        case 'G':
            startiter -= 10;
            break;
        case 'z':
            enditer += 1;
            break;
        case 'h':
            enditer -= 1;
            break;
        case 'Z':
            enditer += 10;
            break;
        case 'H':
            enditer -= 10;
            break;
        case 'v':
        {
            int tmp = enditer;
            enditer = startiter;
            startiter = tmp;
        }
            break;
        case 'u':
            maxiter = maxiter * 20 / 19;
            return;
        case 'j':
            maxiter = maxiter * 19 / 20;
            return;
        case 'U':
            maxiter = maxiter * 5 / 4;
            return;
        case 'J':
            maxiter = maxiter * 4 / 5;
            return;
        case 'r':
            render();
            return;
        case '0':
            center.r = 0;
            center.i = 0;
            scale = 4.0;
            er = 3.0;
            eg = 0.75;
            eb = 0.5;
            startiter = -4;
            enditer = 77;
            maxiter = 8192;
            clear();
            return;
    }
    lastchange = glutGet(GLUT_ELAPSED_TIME);
    redrawflag = 1;
}

void mouseMotion(int x, int y)
{
    if(mpress)
    {
        mpressx2 = x;
        mpressy2 = y;
    }
}

void mouseMotionP(int x, int y)
{
    pointer = center;
    pointer.r += (x - w / 2) * scale / h;
    pointer.i += (y - h / 2) * scale / h;
}

void mouse(int button, int state, int x, int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
            {
                mpress = 1;
                mpressx1 = x;
                mpressy1 = y;
                mpressx2 = x;
                mpressy2 = y;
            }
            else
            {
                double cx, cy, scw, sch;
                mpress = 0;
                mpressx2 = x;
                mpressy2 = y;
                cx = 0.5 * (mpressx1 + mpressx2);
                cy = 0.5 * (mpressy1 + mpressy2);
                center.r += (cx - w / 2) * scale / h;
                center.i += (cy - h / 2) * scale / h;
                scw = fabs(mpressx2 - mpressx1) / w;
                sch = fabs(mpressy2 - mpressy1) / h;
                scale *= MAX(MAX(scw, 0.01), sch);
                clear();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_UP)
            {
                center.r += (x - w / 2) * scale / h;
                center.i += (y - h / 2) * scale / h;
                scale *= 2.0;
                clear();
            }
            break;
        default:
            if(state == GLUT_UP)
            {
                center.r += (x - w / 2) * scale / h;
                center.i += (y - h / 2) * scale / h;
                clear();
            }
    }
}

static void reshape(int ww, int wh)
{
    w = (ww / 8) * 8;
    h = wh;
    if(w != ww)
    {
        reshapeNeeded = 1;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -100, 100); /* left, right, bottom, top, near, far */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h);

    if(cstore) free(cstore);
    if(istore) free(istore);
    if(tex) free(tex);

    cstore = malloc(sizeof(complex) * w * h);
    istore = malloc(sizeof(double) * w * h);
    tex = malloc(sizeof(rgb) * w * h);

    clear();
}

int main(int argc, char* argv[])
{
    int i;
    pthread_t thread;

    pthread_mutex_init(&mline,    NULL);
    pthread_mutex_init(&mworking, NULL);

    for(i = 0; i < 12; ++i)
    {
        pthread_create(&thread, NULL, trender, NULL);
    }
    pthread_create(&thread, NULL, pipereader, NULL);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Mandelbrot (__float128)");

    glutReshapeWindow(1920, 1080);

    glutIdleFunc(idle);
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotionP);

    glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &gltex);
    glBindTexture(GL_TEXTURE_2D, gltex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glutMainLoop();

    return 0;
}
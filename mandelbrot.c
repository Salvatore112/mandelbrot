#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <GL/freeglut.h>

#ifndef _WIN32
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#else
#define popen(x, y) _popen((x), (y))
#endif

#define LIMIT(x, min, max) ((x) > (max) ? (max) : (x) < (min) ? (min) : (x))
#define MAX(x, min) ((x) < (min) ? (min) : (x))
#define MIN(x, max) ((x) > (max) ? (max) : (x))
#define referenceUnusedParameter(a) ((a) = (a))

typedef struct
{
   unsigned char r;
   unsigned char g;
   unsigned char b;
   unsigned char a;
} rgba;

typedef struct
{
   double r;
   double i;
} complex;

complex * cstore;
double * istore;
rgba * tex;

int screenW, screenH;

GLuint gltex;
int iter;
complex pointer = {0, 0};
complex center = {0, 0};
double scale = 4;
int perc = 0;

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

int liveworking = 0;
int livenextline = -1;
pthread_mutex_t mliveline;
pthread_mutex_t mliveworking;

FILE* renderpipe;
char renderstate[256] = "";

complex f(complex x, complex c, double *sqr)
{
   // complex numbers: x * x + c;
   complex res;
   double r2 = x.r * x.r;
   double i2 = x.i * x.i;
   res.r = r2 - i2 + c.r;
   res.i = 2 * x.r * x.i + c.i;
   *sqr = r2 + i2;
   return res;
}

rgba color(double iter)
{
   rgba res;
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
   memset(cstore, 0, sizeof(complex) * screenW * screenH);
   memset(istore, 0, sizeof(double)  * screenW * screenH);
   memset(tex,    0, sizeof(rgba)    * screenW * screenH);
   iter = 0;
   iterperframe = 16;
}

void liverenderline(int y)
{
   int x;
   int index = y * screenW;
   for(x = 0; x < screenW; x++)
   {
      if(istore[index] < 1e-23)
      {
         int localiter = 0;
         complex c = center;
         c.r += (x - screenW / 2) * scale / screenH;
         c.i += (y - screenH / 2) * scale / screenH;
         while(istore[index] < 1e-23 && localiter < iterperframe)
         {
            double sqr;
            cstore[index] = f(cstore[index], c, &sqr);
            if(sqr >= 1e10)
            {
               double diter = iter + localiter - log( 0.5 * log(sqr) / log(2) ) / log(2);
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

void * tliverender(void * a)
{
   referenceUnusedParameter(a);
   for(;;)
   {
      Sleep(1);
      pthread_mutex_lock(&mliveline);
      if(livenextline < 0 || livenextline >= screenH)
      {
         pthread_mutex_unlock(&mliveline);
         continue;
      }
      else
      {
         pthread_mutex_lock(&mliveworking);
         liveworking++;
         pthread_mutex_unlock(&mliveworking);
         for(;;)
         {
            int line = livenextline;
            if(livenextline < 0 || livenextline >= screenH)
            {
               pthread_mutex_unlock(&mliveline);
               break;
            }
            livenextline++;
            pthread_mutex_unlock(&mliveline);

            liverenderline(line);

            pthread_mutex_lock(&mliveline);
         }
      }
      pthread_mutex_lock(&mliveworking);
      liveworking--;
      pthread_mutex_unlock(&mliveworking);
   }
}

void idle(void)
{
   if(reshapeNeeded)
   {
      reshapeNeeded = 0;
      glutReshapeWindow(screenW, screenH);
      return;
   }

   if(iter < maxiter)
   {
      int time1;
      int time2;

      time1 = glutGet(GLUT_ELAPSED_TIME);

      livenextline = 0;

      while(livenextline < screenH || liveworking)
      {
         sched_yield();
      }

      livenextline = -1;

      iter += iterperframe;

      time2 = glutGet(GLUT_ELAPSED_TIME);
      if(time2 < time1 + 20)
      {
         iterperframe += MAX(1, iterperframe / 10);
      }
      else if(time2 > time1 + 35 && iterperframe > 16)
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
   for(y = 0; y < screenH; y++)
   {
      for(x = 0; x < screenW; x++)
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
   for(y = 0; y < screenH; y++)
   {
      for(x = 0; x < screenW; x++)
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
   y = screenH * screenW / 500; // 0.2 % white pixels allowed
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
   char buffer[64];
   glRasterPos2i(10, 35);

   if(perc)
   {
      sprintf(buffer, "%d%%", perc);
   }
   else
   {
      sprintf(buffer, "%d", iter);
   }
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
      glRasterPos2i(10, screenH - 50);
      glutBitmapString(GLUT_BITMAP_9_BY_15, renderstate);
   }

   glRasterPos2i(10, screenH - 35);
   sprintf(buffer, "height %.15lf", scale);
   glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

   glRasterPos2i(10, screenH - 20);
   sprintf(buffer, "center %.15lf + i * %.15lf", center.r, center.i);
   glutBitmapString(GLUT_BITMAP_9_BY_15, buffer);

   glRasterPos2i(10, screenH - 5);
   sprintf(buffer, "pointer %.15lf + i * %.15lf", pointer.r, pointer.i);
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
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenW, screenH, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);

   glBegin(GL_TRIANGLE_STRIP);
   glTexCoord2d(0,0);
   glVertex2d(0,0);
   glTexCoord2d(1,0);
   glVertex2d(screenW,0);
   glTexCoord2d(0,1);
   glVertex2d(0,screenH);
   glTexCoord2d(1,1);
   glVertex2d(screenW,screenH);
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
   referenceUnusedParameter(a);
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
         Sleep(100);
      }
   }
}

void render(void)
{
   if(!renderpipe)
   {
      char buffer[512];
      renderstate[0] = 0;
      #ifdef _WIN32
      sprintf(buffer, "mandelbrot_render.exe 12 %d %d %.16lf %.16lf %.16lf %d %d %d %lf %lf %lf", screenW * 8, screenH * 8, center.r, center.i, scale, startiter, enditer, maxiter, er, eg, eb);
      #else
      sprintf(buffer, "./mandelbrot_render 12 %d %d %.16lf %.16lf %.16lf %d %d %d %lf %lf %lf", screenW * 8, screenH * 8, center.r, center.i, scale, startiter, enditer, maxiter, er, eg, eb);
      #endif
      renderpipe = popen(buffer, "r");
   }
}

static void key(unsigned char key, int x, int y)
{
   referenceUnusedParameter(x);
   referenceUnusedParameter(y);
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
   pointer.r += (x - screenW / 2) * scale / screenH;
   pointer.i += (y - screenH / 2) * scale / screenH;
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
            center.r += (cx - screenW / 2) * scale / screenH;
            center.i += (cy - screenH / 2) * scale / screenH;
            scw = fabs(mpressx2 - mpressx1) / screenW;
            sch = fabs(mpressy2 - mpressy1) / screenH;
            scale *= MAX(MAX(scw, 0.01), sch);
            clear();
         }
         break;
      case GLUT_RIGHT_BUTTON:
         if(state == GLUT_UP)
         {
            center.r += (x - screenW / 2) * scale / screenH;
            center.i += (y - screenH / 2) * scale / screenH;
            scale *= 2.0;
            clear();
         }
         break;
      default:
         if(state == GLUT_UP)
         {
            center.r += (x - screenW / 2) * scale / screenH;
            center.i += (y - screenH / 2) * scale / screenH;
            clear();
         }
   }
}

static void reshape(int w, int h)
{
   screenW = (w / 8) * 8;
   screenH = h;
   if(w != screenW)
   {
      reshapeNeeded = 1;
   }

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, screenW, screenH, 0, -100, 100); /* left, right, bottom, top, near, far */

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glViewport(0, 0, screenW, screenH);

   if(cstore) free(cstore);
   if(istore) free(istore);
   if(tex) free(tex);

   cstore = malloc(sizeof(complex) * screenW * screenH);
   istore = malloc(sizeof(double) * screenW * screenH);
   tex = malloc(sizeof(rgba) * screenW * screenH);

   clear();
}

int main(int argc, char* argv[])
{
   int i;
   pthread_t thread;

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
   glutCreateWindow("Mandelbrot");

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

   pthread_mutex_init(&mliveline,    NULL);
   pthread_mutex_init(&mliveworking, NULL);

   for(i = 0; i < 12; ++i)
   {
      pthread_create(&thread, NULL, tliverender, NULL);
   }
   pthread_create(&thread, NULL, pipereader, NULL);

   glutMainLoop();

   return 0;
}

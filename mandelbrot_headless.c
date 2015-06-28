#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>

#ifndef _WIN32
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
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
} rgb;

typedef struct
{
   double r;
   double i;
} complex;

rgb * rtex;

int w;
int h;

complex center;
double scale;

int startiter;
int enditer;
int maxiter;

double er = 3.0;
double eg = 0.75;
double eb = 0.5;

int renderworking = 0;
int rendernextline = -1;
pthread_mutex_t mrenderline;
pthread_mutex_t mrenderworking;

complex f(complex x, complex c)
{
   // complex numbers: x * x + c;
   complex res;
   res.r = x.r * x.r - x.i * x.i + c.r;
   res.i = 2 * x.r * x.i + c.i;
   return res;
}

double cabssqr(complex c)
{
   return c.i * c.i + c.r * c.r;
}

rgb color(double iter)
{
   rgb res;
   double r, g, b, c;

   c = (iter - startiter) / (enditer - startiter);
   r = pow(c, er);
   g = pow(c, eg);
   b = pow(c, eb);

   res.r = LIMIT(r, 0.0, 1.0) * 255;
   res.g = LIMIT(g, 0.0, 1.0) * 255;
   res.b = LIMIT(b, 0.0, 1.0) * 255;

   return res;
}

void renderline(int y)
{
   int x;
   int index = y * w;
   for(x = 0; x < w; x++)
   {
      int iter = 0;
      int fin = 0;
      complex c = center;
      complex r = {0, 0};
      c.r += (x - w / 2) * scale / h;
      c.i += (y - h / 2) * scale / h;
      while(iter < maxiter && !fin)
      {
         double sqr;
         iter++;
         r = f(r, c);
         sqr = cabssqr(r);
         if(sqr >= 1e10)
         {
            fin = 1;
            rtex[index] = color(iter - log( 0.5 * log(sqr) / log(2) ) / log(2));
         }
      }
      index++;
   }
}

void * trender(void * a)
{
   referenceUnusedParameter(a);
   for(;;)
   {
      Sleep(1);
      pthread_mutex_lock(&mrenderline);
      if(rendernextline < 0 || rendernextline >= h)
      {
         pthread_mutex_unlock(&mrenderline);
         continue;
      }
      else
      {
         pthread_mutex_lock(&mrenderworking);
         renderworking++;
         pthread_mutex_unlock(&mrenderworking);
         for(;;)
         {
            int line = rendernextline;
            if(rendernextline < 0 || rendernextline >= h)
            {
               pthread_mutex_unlock(&mrenderline);
               break;
            }
            rendernextline++;
            pthread_mutex_unlock(&mrenderline);
            
            renderline(line);
            
            pthread_mutex_lock(&mrenderline);
         }
      }
      pthread_mutex_lock(&mrenderworking);
      renderworking--;
      pthread_mutex_unlock(&mrenderworking);
   }
}

void render(void)
{
   char buffer[256];
   FILE*  out;
   long timestamp;
   int perc = 0;

   rtex = malloc(sizeof(rgb) * w * h);
   memset(rtex, 0, sizeof(rgb) * w * h);
   
   rendernextline = 0;
   
   while(rendernextline < h || renderworking)
   {
      int percnew = rendernextline * 100 / h;
      if(perc != percnew)
      {
         perc = percnew;
         printf("\rProgress: %3d%%", perc);
         fflush(stdout);
      }
      sched_yield();
   }

   printf("\rDone.          \n");

   rendernextline = -1;
   perc = 0;
   
   timestamp = (long)time(0);
   sprintf(buffer, "%ld.ppm", timestamp);

   out = fopen(buffer, "wb");
   fprintf(out, "P6\n#center: %0.16lf, %0.16lfi\n#scale: %0.16lf\n%d %d\n255\n", center.r, center.i, scale, w, h);
   fwrite(rtex, sizeof(rgb), w * h, out);
   fclose(out);

   free(rtex);
}

int main(int argc, char* argv[])
{
   int i;
   pthread_t thread;
   
   referenceUnusedParameter(argc);
   
   pthread_mutex_init(&mrenderline,    NULL);
   pthread_mutex_init(&mrenderworking, NULL);
   
   for(i = 0; i < atoi(argv[1]); ++i)
   {
      pthread_create(&thread, NULL, trender, NULL);
   }
   
   w = atoi(argv[2]);
   h = atoi(argv[3]);
   
   center.r = atof(argv[4]);
   center.i = atof(argv[5]);
   
   scale = atof(argv[6]);
   
   startiter = atoi(argv[7]);
   enditer = atoi(argv[8]);
   maxiter = atoi(argv[9]);
   
   render();
   
   return 0;
}

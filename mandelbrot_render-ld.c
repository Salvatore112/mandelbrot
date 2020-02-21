#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>

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
} rgb;

typedef struct
{
   long double r;
   long double i;
} complex;

rgb * tex;

int w;
int h;

complex center;
long double scale;

double er;
double eg;
double eb;
int startiter;
int enditer;
int maxiter;

int working = 0;
int line = -1;
pthread_mutex_t mline;
pthread_mutex_t mworking;

complex f(complex x, complex c, long double *sqr)
{
   // complex numbers: x * x + c;
   complex res;
   long double r2 = x.r * x.r;
   long double i2 = x.i * x.i;
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

void renderline(int y)
{
   int x;
   int index = y * w;
   for(x = 0; x < w; x++)
   {
      int iter = 0;
      complex c = center;
      complex r = {0, 0};
      c.r += (x - w / 2) * scale / h;
      c.i += (y - h / 2) * scale / h;
      while(iter < maxiter)
      {
         long double sqr;
         r = f(r, c, &sqr);
         if(sqr >= 1e10)
         {
            tex[index] = color(iter - log( log(sqr) / log(1e10) ) / log(2));
            break;
         }
         iter++;
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

void render(void)
{
   char buffer[256];
   FILE*  out;
   time_t t1, t2;
   int perc = 0;

   tex = malloc(sizeof(rgb) * w * h);
   memset(tex, 0, sizeof(rgb) * w * h);

   t1 = time(0);
   line = 0;

   while(line < h || working)
   {
      int percnew = line * 100 / h;
      if(perc != percnew)
      {
         perc = percnew;
         printf("Render: %3d%%\n", perc);
         fflush(stdout);
      }
      sleep(1);
   }

   t2 = time(0);
   line = -1;

   printf("Done (%llu s).\n", (unsigned long long)(t2 - t1));
   sprintf(buffer, "%llu.ppm", (unsigned long long)t2);

   out = fopen(buffer, "wb");
   fprintf(out, "P6\n#center: %0.20Lf, %0.20Lfi\n#scale: %0.20Lf\n%d %d\n255\n", center.r, center.i, scale, w, h);
   fwrite(tex, sizeof(rgb), w * h, out);
   fclose(out);

   free(tex);
}

int main(int argc, char* argv[])
{
   int i;
   pthread_t thread;

   pthread_mutex_init(&mline,    NULL);
   pthread_mutex_init(&mworking, NULL);

   for(i = 0; i < atoi(argv[1]); ++i)
   {
      pthread_create(&thread, NULL, trender, NULL);
   }

   w = atoi(argv[2]);
   h = atoi(argv[3]);

   center.r = strtold(argv[4], NULL);
   center.i = strtold(argv[5], NULL);

   scale = strtold(argv[6], NULL);

   startiter = atoi(argv[7]);
   enditer = atoi(argv[8]);
   maxiter = atoi(argv[9]);

   er = atof(argv[10]);
   eg = atof(argv[11]);
   eb = atof(argv[12]);

   render();

   return 0;
}


cl /Femandelbrot.exe /Ox /Ob2 /Oi /Ot /Oy /I../freeglut/include /I../pthreads-w32/include mandelbrot.c /link /LIBPATH:../freeglut/lib /LIBPATH:../pthreads-w32/lib/x86 pthreadVC2.lib

cl /Femandelbrot_render.exe /Ox /Ob2 /Oi /Ot /Oy /I../pthreads-w32/include mandelbrot_render.c /link /LIBPATH:../pthreads-w32/lib/x86 pthreadVC2.lib

del *.obj

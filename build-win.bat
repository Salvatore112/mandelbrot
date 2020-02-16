cl /Femandelbrot.exe /D_CRT_SECURE_NO_WARNINGS /W3 /Ox /Ob2 /Oi /Ot /Oy /I../freeglut/include /I../pthreads4w mandelbrot.c /link /LIBPATH:../freeglut/lib/x64 /LIBPATH:../pthreads4w pthreadVC2.lib

cl /Femandelbrot_render.exe /D_CRT_SECURE_NO_WARNINGS /W3 /Ox /Ob2 /Oi /Ot /Oy /I../pthreads4w mandelbrot_render.c /link /LIBPATH:../pthreads4w pthreadVC2.lib

del *.obj

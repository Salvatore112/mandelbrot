# mandelbrot
mandelbrot fractal explorer and renderer

- written in c
- multithreaded (pthreads)
- rendering with glut (opengl)
- interactive zooming (mark rectangle with mouse)
- automatic color scaling (press f)
- renders .ppm with 8x oversampling (press r)

# Code analysis (Homework)

After the build the following binaries were generated:

- mandelbrot
- mandelbrot_render
- mandelbrot_render-ld
- mandelbrot-f128
- mandelbrot-ld

After running "valgrind --tool=helgrind" on the these files, the following output for each was given:

## mandelbrot

<details>
<summary>Output</summary>
<br>
```
==5581== Helgrind, a thread error detector
==5581== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==5581== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5581== Command: ./mandelbrot
==5581== 
==5581== ---Thread-Announcement------------------------------------------
==5581== 
==5581== Thread #1 is the program's root thread
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x5046490 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0xBDA15E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC399FE8: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBD3D623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3946A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3945E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBD3DEEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBD47265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBB5B142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==5581==    by 0xBB60FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==5581==    by 0xBB5C745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==5581==    by 0xBB5D0F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==5581==  Address 0x5046490 is 624 bytes inside a block of size 936 alloc'd
==5581==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0xC399DF6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBD3D623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3946A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3945E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBD3DEEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBD47265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBB5B142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==5581==    by 0xBB60FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==5581==    by 0xBB5C745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==5581==    by 0xBB5D0F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==5581==    by 0x4D3279A: glXChooseFBConfig (in /usr/lib/x86_64-linux-gnu/libGLX.so.0.0.0)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== Possible data race during read of size 1 at 0x25ECB3B0 by thread #1
==5581== Locks held: 1, at address 0x5046490
==5581==    at 0x485077C: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4850A2A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0xC39C500: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC39F9AC: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3AD6DA: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC39C75B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xBDF1216: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0x4917769: glutSwapBuffers (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x492172A: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==  Address 0x25ecb3b0 is 16 bytes inside a block of size 112 alloc'd
==5581==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0xC39C49B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3AD18C: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3AD74F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3AECC4: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC3B628E: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC319143: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC314958: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC314DA1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC2AC7D1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC2A5AE9: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==    by 0xC2A5E93: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== ---Thread-Announcement------------------------------------------
==5581== 
==5581== Thread #9 was created
==5581==    at 0x4B589F3: clone (clone.S:76)
==5581==    by 0x4B598EE: __clone_internal (clone-internal.c:83)
==5581==    by 0x4AC76D8: create_thread (pthread_create.c:295)
==5581==    by 0x4AC81FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==5581==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A706: main (in /home/pasha/mandelbrot/mandelbrot)
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x10F1E0 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==5581== 
==5581== Possible data race during write of size 4 at 0x10F010 by thread #1
==5581== Locks held: none
==5581==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581== 
==5581== This conflicts with a previous read of size 4 by thread #9
==5581== Locks held: 1, at address 0x10F1E0
==5581==    at 0x10B37A: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f010 is 0 bytes inside data symbol "line"
==5581== 
==5581== ---Thread-Announcement------------------------------------------
==5581== 
==5581== Thread #10 was created
==5581==    at 0x4B589F3: clone (clone.S:76)
==5581==    by 0x4B598EE: __clone_internal (clone-internal.c:83)
==5581==    by 0x4AC76D8: create_thread (pthread_create.c:295)
==5581==    by 0x4AC81FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==5581==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A706: main (in /home/pasha/mandelbrot/mandelbrot)
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x10F1E0 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==5581== 
==5581== Possible data race during read of size 4 at 0x10F010 by thread #10
==5581== Locks held: 1, at address 0x10F1E0
==5581==    at 0x10B37A: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581== 
==5581== This conflicts with a previous write of size 4 by thread #1
==5581== Locks held: none
==5581==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f010 is 0 bytes inside data symbol "line"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x10F1E0 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==5581== 
==5581== Possible data race during read of size 4 at 0x10F260 by thread #10
==5581== Locks held: 1, at address 0x10F1E0
==5581==    at 0x10B384: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f260 is 0 bytes inside data symbol "h"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x10F1E0 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==5581== 
==5581== Possible data race during read of size 4 at 0x10F010 by thread #10
==5581== Locks held: 1, at address 0x10F1E0
==5581==    at 0x10B3A2: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581== 
==5581== This conflicts with a previous write of size 4 by thread #1
==5581== Locks held: none
==5581==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f010 is 0 bytes inside data symbol "line"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x10F1E0 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==5581== 
==5581== Possible data race during read of size 4 at 0x10F260 by thread #10
==5581== Locks held: 1, at address 0x10F1E0
==5581==    at 0x10B3DA: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f260 is 0 bytes inside data symbol "h"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x10F1E0 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==5581== 
==5581== Possible data race during write of size 4 at 0x10F010 by thread #10
==5581== Locks held: 1, at address 0x10F1E0
==5581==    at 0x10B3B6: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581== 
==5581== This conflicts with a previous write of size 4 by thread #1
==5581== Locks held: none
==5581==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f010 is 0 bytes inside data symbol "line"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 4 at 0x10F264 by thread #10
==5581== Locks held: none
==5581==    at 0x10B175: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f264 is 0 bytes inside data symbol "w"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 8 at 0x10F270 by thread #10
==5581== Locks held: none
==5581==    at 0x10B1A0: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f270 is 0 bytes inside data symbol "istore"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 8 at 0x27F17040 by thread #10
==5581== Locks held: none
==5581==    at 0x10B1D2: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x27f17040 is 0 bytes inside a block of size 16,588,800 alloc'd
==5581==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10B132: reshape (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 4 at 0x10F260 by thread #10
==5581== Locks held: none
==5581==    at 0x10B1DA: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f260 is 0 bytes inside data symbol "h"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 4 at 0x10F014 by thread #10
==5581== Locks held: none
==5581==    at 0x10B216: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f014 is 0 bytes inside data symbol "iterperframe"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 8 at 0x10F278 by thread #10
==5581== Locks held: none
==5581==    at 0x10B25C: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f278 is 0 bytes inside data symbol "cstore"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 8 at 0x25F72040 by thread #10
==5581== Locks held: none
==5581==    at 0x10B266: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x25f72040 is 0 bytes inside a block of size 33,177,600 alloc'd
==5581==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10B11E: reshape (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 8 at 0x25F72048 by thread #10
==5581== Locks held: none
==5581==    at 0x10B26A: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x25f72048 is 8 bytes inside a block of size 33,177,600 alloc'd
==5581==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10B11E: reshape (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during write of size 8 at 0x25F72040 by thread #10
==5581== Locks held: none
==5581==    at 0x10B293: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x25f72040 is 0 bytes inside a block of size 33,177,600 alloc'd
==5581==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10B11E: reshape (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 8 at 0x27F17040 by thread #10
==5581== Locks held: none
==5581==    at 0x10B240: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x27f17040 is 0 bytes inside a block of size 16,588,800 alloc'd
==5581==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10B132: reshape (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 4 at 0x10F22C by thread #10
==5581== Locks held: none
==5581==    at 0x10B299: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f22c is 0 bytes inside data symbol "iter"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during write of size 8 at 0x27F17040 by thread #10
==5581== Locks held: none
==5581==    at 0x10B2E9: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x27f17040 is 0 bytes inside a block of size 16,588,800 alloc'd
==5581==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10B132: reshape (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during read of size 8 at 0x10F268 by thread #10
==5581== Locks held: none
==5581==    at 0x10B2FA: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f268 is 0 bytes inside data symbol "tex"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581== Possible data race during write of size 4 at 0x28EEA040 by thread #10
==5581== Locks held: none
==5581==    at 0x10B306: renderline (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x28eea040 is 0 bytes inside a block of size 8,294,400 alloc'd
==5581==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10B146: reshape (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Block was alloc'd by thread #1
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x10F1E0 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==5581== 
==5581== Possible data race during read of size 4 at 0x10F010 by thread #10
==5581== Locks held: 1, at address 0x10F1E0
==5581==    at 0x10B3D0: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581== 
==5581== This conflicts with a previous write of size 4 by thread #1
==5581== Locks held: none
==5581==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f010 is 0 bytes inside data symbol "line"
==5581== 
==5581== ----------------------------------------------------------------
==5581== 
==5581==  Lock at 0x10F1E0 was first observed
==5581==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==5581==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==5581== 
==5581== Possible data race during read of size 4 at 0x10F010 by thread #1
==5581== Locks held: none
==5581==    at 0x10A9F5: idle (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==5581==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==5581== 
==5581== This conflicts with a previous write of size 4 by thread #10
==5581== Locks held: 1, at address 0x10F1E0
==5581==    at 0x10B3B6: trender (in /home/pasha/mandelbrot/mandelbrot)
==5581==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==5581==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==5581==    by 0x4B58A03: clone (clone.S:100)
==5581==  Address 0x10f010 is 0 bytes inside data symbol "line"
==5581== 
==5581== 
==5581== More than 10000000 total errors detected.  I'm not reporting any more.
==5581== Final error counts will be inaccurate.  Go fix your program!
==5581== Rerun with --error-limit=no to disable this cutoff.  Note
==5581== that errors may occur in your program without prior warning from
==5581== Valgrind, because errors are no longer being displayed.
==5581==
```
</details>

## mandelbrot
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
- mandelbrot_render (Seg fault occured while trying to analyze it with helgrind) 
- mandelbrot_render-ld (Seg fault occured while trying to analyze it with helgrind)
- mandelbrot-f128
- mandelbrot-ld

After running "valgrind --tool=helgrind" on the these files, the following output for each was given:

## mandelbrot

<details>
<summary>helgrind report (before fixes)</summary>

``` 
==3297== Helgrind, a thread error detector
==3297== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==3297== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==3297== Command: ./mandelbrot
==3297== 
==3297== ---Thread-Announcement------------------------------------------
==3297== 
==3297== Thread #1 is the program's root thread
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297==  Lock at 0x5046490 was first observed
==3297==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0xBDA15E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC399FE8: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBD3D623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3946A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3945E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBD3DEEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBD47265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBB5B142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3297==    by 0xBB60FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3297==    by 0xBB5C745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3297==    by 0xBB5D0F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3297==  Address 0x5046490 is 624 bytes inside a block of size 936 alloc'd
==3297==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0xC399DF6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBD3D623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3946A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3945E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBD3DEEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBD47265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBB5B142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3297==    by 0xBB60FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3297==    by 0xBB5C745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3297==    by 0xBB5D0F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3297==    by 0x4D3279A: glXChooseFBConfig (in /usr/lib/x86_64-linux-gnu/libGLX.so.0.0.0)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== Possible data race during read of size 1 at 0x25ECB3B0 by thread #1
==3297== Locks held: 1, at address 0x5046490
==3297==    at 0x485077C: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4850A2A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0xC39C500: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC39F9AC: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3AD6DA: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC39C75B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xBDF1216: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0x4917769: glutSwapBuffers (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x492172A: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==  Address 0x25ecb3b0 is 16 bytes inside a block of size 112 alloc'd
==3297==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0xC39C49B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3AD18C: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3AD74F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3AECC4: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC3B628E: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC319143: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC314958: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC314DA1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC2AC7D1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC2A5AE9: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==    by 0xC2A5E93: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== ---Thread-Announcement------------------------------------------
==3297== 
==3297== Thread #4 was created
==3297==    at 0x4B589F3: clone (clone.S:76)
==3297==    by 0x4B598EE: __clone_internal (clone-internal.c:83)
==3297==    by 0x4AC76D8: create_thread (pthread_create.c:295)
==3297==    by 0x4AC81FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3297==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A706: main (in /home/pasha/mandelbrot/mandelbrot)
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297==  Lock at 0x10F1E0 was first observed
==3297==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3297== 
==3297== Possible data race during write of size 4 at 0x10F010 by thread #1
==3297== Locks held: none
==3297==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297== 
==3297== This conflicts with a previous read of size 4 by thread #4
==3297== Locks held: 1, at address 0x10F1E0
==3297==    at 0x10B37A: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3297== 
==3297== ---Thread-Announcement------------------------------------------
==3297== 
==3297== Thread #11 was created
==3297==    at 0x4B589F3: clone (clone.S:76)
==3297==    by 0x4B598EE: __clone_internal (clone-internal.c:83)
==3297==    by 0x4AC76D8: create_thread (pthread_create.c:295)
==3297==    by 0x4AC81FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3297==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A706: main (in /home/pasha/mandelbrot/mandelbrot)
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297==  Lock at 0x10F1E0 was first observed
==3297==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3297== 
==3297== Possible data race during read of size 4 at 0x10F010 by thread #11
==3297== Locks held: 1, at address 0x10F1E0
==3297==    at 0x10B37A: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297== 
==3297== This conflicts with a previous write of size 4 by thread #1
==3297== Locks held: none
==3297==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297==  Lock at 0x10F1E0 was first observed
==3297==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3297== 
==3297== Possible data race during read of size 4 at 0x10F260 by thread #11
==3297== Locks held: 1, at address 0x10F1E0
==3297==    at 0x10B384: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f260 is 0 bytes inside data symbol "h"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297==  Lock at 0x10F1E0 was first observed
==3297==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3297== 
==3297== Possible data race during read of size 4 at 0x10F010 by thread #11
==3297== Locks held: 1, at address 0x10F1E0
==3297==    at 0x10B3A2: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297== 
==3297== This conflicts with a previous write of size 4 by thread #1
==3297== Locks held: none
==3297==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297==  Lock at 0x10F1E0 was first observed
==3297==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3297== 
==3297== Possible data race during read of size 4 at 0x10F260 by thread #11
==3297== Locks held: 1, at address 0x10F1E0
==3297==    at 0x10B3DA: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f260 is 0 bytes inside data symbol "h"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297==  Lock at 0x10F1E0 was first observed
==3297==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3297== 
==3297== Possible data race during write of size 4 at 0x10F010 by thread #11
==3297== Locks held: 1, at address 0x10F1E0
==3297==    at 0x10B3B6: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297== 
==3297== This conflicts with a previous write of size 4 by thread #1
==3297== Locks held: none
==3297==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 4 at 0x10F264 by thread #11
==3297== Locks held: none
==3297==    at 0x10B175: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f264 is 0 bytes inside data symbol "w"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 8 at 0x10F270 by thread #11
==3297== Locks held: none
==3297==    at 0x10B1A0: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f270 is 0 bytes inside data symbol "istore"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 8 at 0x27F17040 by thread #11
==3297== Locks held: none
==3297==    at 0x10B1D2: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x27f17040 is 0 bytes inside a block of size 16,588,800 alloc'd
==3297==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10B132: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 4 at 0x10F260 by thread #11
==3297== Locks held: none
==3297==    at 0x10B1DA: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f260 is 0 bytes inside data symbol "h"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 4 at 0x10F014 by thread #11
==3297== Locks held: none
==3297==    at 0x10B216: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f014 is 0 bytes inside data symbol "iterperframe"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 8 at 0x10F278 by thread #11
==3297== Locks held: none
==3297==    at 0x10B25C: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f278 is 0 bytes inside data symbol "cstore"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 8 at 0x25F72040 by thread #11
==3297== Locks held: none
==3297==    at 0x10B266: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x25f72040 is 0 bytes inside a block of size 33,177,600 alloc'd
==3297==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10B11E: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 8 at 0x25F72048 by thread #11
==3297== Locks held: none
==3297==    at 0x10B26A: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x25f72048 is 8 bytes inside a block of size 33,177,600 alloc'd
==3297==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10B11E: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during write of size 8 at 0x25F72040 by thread #11
==3297== Locks held: none
==3297==    at 0x10B293: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x25f72040 is 0 bytes inside a block of size 33,177,600 alloc'd
==3297==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10B11E: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 8 at 0x27F17040 by thread #11
==3297== Locks held: none
==3297==    at 0x10B240: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x27f17040 is 0 bytes inside a block of size 16,588,800 alloc'd
==3297==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10B132: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 4 at 0x10F22C by thread #11
==3297== Locks held: none
==3297==    at 0x10B299: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f22c is 0 bytes inside data symbol "iter"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during write of size 8 at 0x27F17040 by thread #11
==3297== Locks held: none
==3297==    at 0x10B2E9: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x27f17040 is 0 bytes inside a block of size 16,588,800 alloc'd
==3297==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10B132: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during read of size 8 at 0x10F268 by thread #11
==3297== Locks held: none
==3297==    at 0x10B2FA: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x10f268 is 0 bytes inside data symbol "tex"
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297== Possible data race during write of size 4 at 0x28EEA040 by thread #11
==3297== Locks held: none
==3297==    at 0x10B306: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297==  Address 0x28eea040 is 0 bytes inside a block of size 8,294,400 alloc'd
==3297==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10B146: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Block was alloc'd by thread #1
==3297== 
==3297== ----------------------------------------------------------------
==3297== 
==3297==  Lock at 0x10F1E0 was first observed
==3297==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3297== 
==3297== Possible data race during read of size 4 at 0x10F010 by thread #11
==3297== Locks held: 1, at address 0x10F1E0
==3297==    at 0x10B3D0: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297== 
==3297== This conflicts with a previous write of size 4 by thread #1
==3297== Locks held: none
==3297==    at 0x10A9E4: idle (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3297==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot)
==3297==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3297== 
==3297== 
==3297== More than 10000000 total errors detected.  I'm not reporting any more.
==3297== Final error counts will be inaccurate.  Go fix your program!
==3297== Rerun with --error-limit=no to disable this cutoff.  Note
==3297== that errors may occur in your program without prior warning from
==3297== Valgrind, because errors are no longer being displayed.
==3297== 
^C==3297== 
==3297== Process terminating with default action of signal 2 (SIGINT)
==3297==    at 0x495A300: ??? (in /usr/lib/x86_64-linux-gnu/libm.so.6)
==3297==    by 0x4983E47: pow@@GLIBC_2.29 (w_pow_template.c:32)
==3297==    by 0x10ACB7: color (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B2F9: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x10B3C7: trender (in /home/pasha/mandelbrot/mandelbrot)
==3297==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3297==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3297==    by 0x4B58A03: clone (clone.S:100)
==3297== 
==3297== Use --history-level=approx or =none to gain increased speed, at
==3297== the cost of reduced accuracy of conflicting-access information
==3297== For lists of detected and suppressed errors, rerun with: -s
==3297== ERROR SUMMARY: 10000000 errors from 22 contexts (suppressed: 13491 from 51)
```
</details>
<details>
<summary>helgrind report (after fixes)</summary>

``` 
==3662== Helgrind, a thread error detector
==3662== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==3662== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==3662== Command: ./mandelbrot
==3662== 
==3662== ---Thread-Announcement------------------------------------------
==3662== 
==3662== Thread #1 is the program's root thread
==3662== 
==3662== ---Thread-Announcement------------------------------------------
==3662== 
==3662== Thread #31 was created
==3662==    at 0x4BB09F3: clone (clone.S:76)
==3662==    by 0x4BB18EE: __clone_internal (clone-internal.c:83)
==3662==    by 0x4B1F6D8: create_thread (pthread_create.c:295)
==3662==    by 0x4B201FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3662==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10A70F: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during write of size 4 at 0x10E010 by thread #1
==3662== Locks held: none
==3662==    at 0x10A924: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== 
==3662== This conflicts with a previous read of size 4 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B2CA: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e010 is 0 bytes inside data symbol "line"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during read of size 4 at 0x10E010 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B2CA: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662== 
==3662== This conflicts with a previous write of size 4 by thread #1
==3662== Locks held: none
==3662==    at 0x10A924: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662==  Address 0x10e010 is 0 bytes inside data symbol "line"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during read of size 4 at 0x10E2A0 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B2D4: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662== 
==3662== This conflicts with a previous write of size 4 by thread #1
==3662== Locks held: none
==3662==    at 0x10AE52: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x4977D5A: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x4978578: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662==  Address 0x10e2a0 is 0 bytes inside data symbol "h"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during read of size 4 at 0x10E010 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B2F2: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662== 
==3662== This conflicts with a previous write of size 4 by thread #1
==3662== Locks held: none
==3662==    at 0x10A924: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662==  Address 0x10e010 is 0 bytes inside data symbol "line"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during write of size 4 at 0x10E010 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B306: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662== 
==3662== This conflicts with a previous write of size 4 by thread #1
==3662== Locks held: none
==3662==    at 0x10A924: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662==  Address 0x10e010 is 0 bytes inside data symbol "line"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during read of size 4 at 0x10E010 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B320: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662== 
==3662== This conflicts with a previous write of size 4 by thread #1
==3662== Locks held: none
==3662==    at 0x10A924: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662==  Address 0x10e010 is 0 bytes inside data symbol "line"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during read of size 4 at 0x10E010 by thread #1
==3662== Locks held: none
==3662==    at 0x10A935: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== 
==3662== This conflicts with a previous write of size 4 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B306: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e010 is 0 bytes inside data symbol "line"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662== Possible data race during read of size 4 at 0x10E248 by thread #1
==3662== Locks held: none
==3662==    at 0x10A943: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662==  Address 0x10e248 is 0 bytes inside data symbol "working"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E1E0 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10AA4F: pipereader (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e1e0 is 0 bytes inside data symbol "mworking"
==3662== 
==3662== Possible data race during write of size 4 at 0x10E248 by thread #31
==3662== Locks held: 1, at address 0x10E1E0
==3662==    at 0x10B345: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662== 
==3662== This conflicts with a previous read of size 4 by thread #1
==3662== Locks held: none
==3662==    at 0x10A943: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662==  Address 0x10e248 is 0 bytes inside data symbol "working"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662== Possible data race during write of size 4 at 0x10E26C by thread #1
==3662== Locks held: none
==3662==    at 0x10A958: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== 
==3662== This conflicts with a previous read of size 4 by thread #31
==3662== Locks held: none
==3662==    at 0x10B1E5: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x10B317: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e26c is 0 bytes inside data symbol "iter"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during write of size 4 at 0x10E010 by thread #1
==3662== Locks held: none
==3662==    at 0x10A95E: idle (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x49785BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== 
==3662== This conflicts with a previous read of size 4 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B320: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e010 is 0 bytes inside data symbol "line"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x5490E90 was first observed
==3662==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x63B85E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69B0FE8: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x6354623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69AB6A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69AB5E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x6354EEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x635E265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x6172142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3662==    by 0x6177FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3662==    by 0x6173745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3662==    by 0x61740F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3662==  Address 0x5490e90 is 624 bytes inside a block of size 936 alloc'd
==3662==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x69B0DF6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x6354623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69AB6A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69AB5E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x6354EEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x635E265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x6172142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3662==    by 0x6177FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3662==    by 0x6173745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3662==    by 0x61740F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3662==    by 0x4D8879A: glXChooseFBConfig (in /usr/lib/x86_64-linux-gnu/libGLX.so.0.0.0)
==3662==  Block was alloc'd by thread #1
==3662== 
==3662== Possible data race during read of size 1 at 0x216F67E0 by thread #1
==3662== Locks held: 1, at address 0x5490E90
==3662==    at 0x485077C: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4850A2A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x69B3500: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69B69AC: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69C46DA: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69B375B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x6408216: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x496D769: glutSwapBuffers (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x497772A: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x497B0C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x4977CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x49785D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==  Address 0x216f67e0 is 16 bytes inside a block of size 112 alloc'd
==3662==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x69B349B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69C418C: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69C474F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69C5CC4: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x69CD28E: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x6930143: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x692B958: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x692BDA1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x68C37D1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x68BCAE9: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==    by 0x68BCE93: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3662==  Block was alloc'd by thread #1
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662== Possible data race during write of size 4 at 0x10E2A4 by thread #1
==3662== Locks held: none
==3662==    at 0x10AE49: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x4977D5A: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x49785D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== 
==3662== This conflicts with a previous read of size 4 by thread #31
==3662== Locks held: none
==3662==    at 0x10B0B5: renderline (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x10B317: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e2a4 is 0 bytes inside data symbol "w"
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662==  Lock at 0x10E220 was first observed
==3662==    at 0x4850CCF: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10B2C9: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e220 is 0 bytes inside data symbol "mline"
==3662== 
==3662== Possible data race during write of size 4 at 0x10E2A0 by thread #1
==3662== Locks held: none
==3662==    at 0x10AE52: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x4977D5A: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x49785D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== 
==3662== This conflicts with a previous read of size 4 by thread #31
==3662== Locks held: 1, at address 0x10E220
==3662==    at 0x10B32A: trender (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662==  Address 0x10e2a0 is 0 bytes inside data symbol "h"
==3662== 
^C==3662== 
==3662== Process terminating with default action of signal 2 (SIGINT)
==3662==    at 0x4A188B0: __ieee754_pow_fma (e_pow.c:283)
==3662==    by 0x49D9E47: pow@@GLIBC_2.29 (w_pow_template.c:32)
==3662==    by 0x10AD74: color (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x10AF93: reshape (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x4977D5A: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x49785D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3662==    by 0x10A771: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== ---Thread-Announcement------------------------------------------
==3662== 
==3662== Thread #32 was created
==3662==    at 0x4BB09F3: clone (clone.S:76)
==3662==    by 0x4BB18EE: __clone_internal (clone-internal.c:83)
==3662==    by 0x4B1F6D8: create_thread (pthread_create.c:295)
==3662==    by 0x4B201FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3662==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x10A724: main (in /home/pasha/mandelbrot/mandelbrot)
==3662== 
==3662== ----------------------------------------------------------------
==3662== 
==3662== Thread #32: Exiting thread still holds 1 lock
==3662==    at 0x4B707F8: clock_nanosleep@@GLIBC_2.17 (clock_nanosleep.c:78)
==3662==    by 0x4B75676: nanosleep (nanosleep.c:25)
==3662==    by 0x4BA6F2E: usleep (usleep.c:31)
==3662==    by 0x10AA99: pipereader (in /home/pasha/mandelbrot/mandelbrot)
==3662==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3662==    by 0x4B1FAC2: start_thread (pthread_create.c:442)
==3662==    by 0x4BB0A03: clone (clone.S:100)
==3662== 
==3662== 
==3662== Use --history-level=approx or =none to gain increased speed, at
==3662== the cost of reduced accuracy of conflicting-access information
==3662== For lists of detected and suppressed errors, rerun with: -s
==3662== ERROR SUMMARY: 17040 errors from 15 contexts (suppressed: 16901 from 72)
```
</details>

## mandlebrot-f128
```
==3342== Helgrind, a thread error detector
==3342== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==3342== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==3342== Command: ./mandelbrot-f128
==3342== 
==3342== ---Thread-Announcement------------------------------------------
==3342== 
==3342== Thread #1 is the program's root thread
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x5090590 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0xBDE95E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3E1FE8: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBD85623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3DC6A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3DC5E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBD85EEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBD8F265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBBA3142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3342==    by 0xBBA8FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3342==    by 0xBBA4745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3342==    by 0xBBA50F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3342==  Address 0x5090590 is 624 bytes inside a block of size 936 alloc'd
==3342==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0xC3E1DF6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBD85623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3DC6A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3DC5E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBD85EEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBD8F265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBBA3142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3342==    by 0xBBA8FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3342==    by 0xBBA4745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3342==    by 0xBBA50F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3342==    by 0x4D7A79A: glXChooseFBConfig (in /usr/lib/x86_64-linux-gnu/libGLX.so.0.0.0)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== Possible data race during read of size 1 at 0x25F14CC0 by thread #1
==3342== Locks held: 1, at address 0x5090590
==3342==    at 0x485077C: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4850A2A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0xC3E4500: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3E79AC: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3F56DA: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3E475B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xBE39216: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0x4917769: glutSwapBuffers (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x492172A: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==  Address 0x25f14cc0 is 16 bytes inside a block of size 112 alloc'd
==3342==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0xC3E449B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3F518C: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3F574F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3F6CC4: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC3FE28E: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC361143: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC35C958: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC35CDA1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC2F47D1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC2EDAE9: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==    by 0xC2EDE93: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ---Thread-Announcement------------------------------------------
==3342== 
==3342== Thread #7 was created
==3342==    at 0x4BA29F3: clone (clone.S:76)
==3342==    by 0x4BA38EE: __clone_internal (clone-internal.c:83)
==3342==    by 0x4B116D8: create_thread (pthread_create.c:295)
==3342==    by 0x4B121FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3342==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A746: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x1141E0 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A723: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x1141e0 is 0 bytes inside data symbol "mline"
==3342== 
==3342== Possible data race during write of size 4 at 0x114010 by thread #1
==3342== Locks held: none
==3342==    at 0x10AA84: idle (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342== 
==3342== This conflicts with a previous read of size 4 by thread #7
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B86A: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114010 is 0 bytes inside data symbol "line"
==3342== 
==3342== ---Thread-Announcement------------------------------------------
==3342== 
==3342== Thread #10 was created
==3342==    at 0x4BA29F3: clone (clone.S:76)
==3342==    by 0x4BA38EE: __clone_internal (clone-internal.c:83)
==3342==    by 0x4B116D8: create_thread (pthread_create.c:295)
==3342==    by 0x4B121FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3342==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A746: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x1141E0 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A723: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x1141e0 is 0 bytes inside data symbol "mline"
==3342== 
==3342== Possible data race during read of size 4 at 0x114010 by thread #10
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B86A: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342== 
==3342== This conflicts with a previous write of size 4 by thread #1
==3342== Locks held: none
==3342==    at 0x10AA84: idle (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x114010 is 0 bytes inside data symbol "line"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x1141E0 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A723: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x1141e0 is 0 bytes inside data symbol "mline"
==3342== 
==3342== Possible data race during read of size 4 at 0x114280 by thread #10
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B874: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114280 is 0 bytes inside data symbol "h"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x1141E0 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A723: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x1141e0 is 0 bytes inside data symbol "mline"
==3342== 
==3342== Possible data race during read of size 4 at 0x114010 by thread #10
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B892: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342== 
==3342== This conflicts with a previous write of size 4 by thread #1
==3342== Locks held: none
==3342==    at 0x10AA84: idle (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x114010 is 0 bytes inside data symbol "line"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x1141E0 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A723: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x1141e0 is 0 bytes inside data symbol "mline"
==3342== 
==3342== Possible data race during read of size 4 at 0x114280 by thread #10
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B8CA: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114280 is 0 bytes inside data symbol "h"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x1141E0 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A723: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x1141e0 is 0 bytes inside data symbol "mline"
==3342== 
==3342== Possible data race during write of size 4 at 0x114010 by thread #10
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B8A6: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342== 
==3342== This conflicts with a previous write of size 4 by thread #1
==3342== Locks held: none
==3342==    at 0x10AA84: idle (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x114010 is 0 bytes inside data symbol "line"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 4 at 0x114284 by thread #10
==3342== Locks held: none
==3342==    at 0x10B587: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114284 is 0 bytes inside data symbol "w"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 8 at 0x114290 by thread #10
==3342== Locks held: none
==3342==    at 0x10B5B1: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114290 is 0 bytes inside data symbol "istore"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 8 at 0x29F03040 by thread #10
==3342== Locks held: none
==3342==    at 0x10B5E2: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x29f03040 is 0 bytes inside a block of size 16,588,800 alloc'd
==3342==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10B542: reshape (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 4 at 0x114280 by thread #10
==3342== Locks held: none
==3342==    at 0x10B5EB: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114280 is 0 bytes inside data symbol "h"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 4 at 0x114014 by thread #10
==3342== Locks held: none
==3342==    at 0x10B683: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114014 is 0 bytes inside data symbol "iterperframe"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 8 at 0x114298 by thread #10
==3342== Locks held: none
==3342==    at 0x10B6BD: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114298 is 0 bytes inside data symbol "cstore"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 8 at 0x25FBA040 by thread #10
==3342== Locks held: none
==3342==    at 0x10B6C7: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x25fba040 is 0 bytes inside a block of size 66,355,200 alloc'd
==3342==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10B52E: reshape (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 8 at 0x25FBA050 by thread #10
==3342== Locks held: none
==3342==    at 0x10B6CC: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x25fba050 is 16 bytes inside a block of size 66,355,200 alloc'd
==3342==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10B52E: reshape (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during write of size 8 at 0x25FBA040 by thread #10
==3342== Locks held: none
==3342==    at 0x10B744: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x25fba040 is 0 bytes inside a block of size 66,355,200 alloc'd
==3342==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10B52E: reshape (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during write of size 8 at 0x25FBA050 by thread #10
==3342== Locks held: none
==3342==    at 0x10B770: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x25fba050 is 16 bytes inside a block of size 66,355,200 alloc'd
==3342==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10B52E: reshape (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 4 at 0x11422C by thread #10
==3342== Locks held: none
==3342==    at 0x10B792: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x11422c is 0 bytes inside data symbol "iter"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during write of size 8 at 0x29F03040 by thread #10
==3342== Locks held: none
==3342==    at 0x10B7E1: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x29f03040 is 0 bytes inside a block of size 16,588,800 alloc'd
==3342==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10B542: reshape (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 8 at 0x114288 by thread #10
==3342== Locks held: none
==3342==    at 0x10B7F2: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114288 is 0 bytes inside data symbol "tex"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during write of size 4 at 0x2AED6040 by thread #10
==3342== Locks held: none
==3342==    at 0x10B7FE: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x2aed6040 is 0 bytes inside a block of size 8,294,400 alloc'd
==3342==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10B556: reshape (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342== Possible data race during read of size 8 at 0x29F03590 by thread #10
==3342== Locks held: none
==3342==    at 0x10B698: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x29f03590 is 1,360 bytes inside a block of size 16,588,800 alloc'd
==3342==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10B542: reshape (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Block was alloc'd by thread #1
==3342== 
==3342== ---Thread-Announcement------------------------------------------
==3342== 
==3342== Thread #6 was created
==3342==    at 0x4BA29F3: clone (clone.S:76)
==3342==    by 0x4BA38EE: __clone_internal (clone-internal.c:83)
==3342==    by 0x4B116D8: create_thread (pthread_create.c:295)
==3342==    by 0x4B121FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3342==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A746: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342== 
==3342== ---Thread-Announcement------------------------------------------
==3342== 
==3342== Thread #11 was created
==3342==    at 0x4BA29F3: clone (clone.S:76)
==3342==    by 0x4BA38EE: __clone_internal (clone-internal.c:83)
==3342==    by 0x4B116D8: create_thread (pthread_create.c:295)
==3342==    by 0x4B121FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3342==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A746: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x1141E0 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A723: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x1141e0 is 0 bytes inside data symbol "mline"
==3342== 
==3342== Possible data race during read of size 4 at 0x114010 by thread #6
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B8C0: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342== 
==3342== This conflicts with a previous write of size 4 by thread #11
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B8A6: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114010 is 0 bytes inside data symbol "line"
==3342== 
==3342== ----------------------------------------------------------------
==3342== 
==3342==  Lock at 0x1141E0 was first observed
==3342==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x10A723: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==  Address 0x1141e0 is 0 bytes inside data symbol "mline"
==3342== 
==3342== Possible data race during read of size 4 at 0x114010 by thread #1
==3342== Locks held: none
==3342==    at 0x10AA95: idle (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3342==    by 0x10A83B: main (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342== 
==3342== This conflicts with a previous write of size 4 by thread #10
==3342== Locks held: 1, at address 0x1141E0
==3342==    at 0x10B8A6: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342==  Address 0x114010 is 0 bytes inside data symbol "line"
==3342== 
==3342== 
==3342== More than 10000000 total errors detected.  I'm not reporting any more.
==3342== Final error counts will be inaccurate.  Go fix your program!
==3342== Rerun with --error-limit=no to disable this cutoff.  Note
==3342== that errors may occur in your program without prior warning from
==3342== Valgrind, because errors are no longer being displayed.
==3342== 
^C==3342== 
==3342== Process terminating with default action of signal 2 (SIGINT)
==3342==    at 0x10B6EB: renderline (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x10B8B7: trender (in /home/pasha/mandelbrot/mandelbrot-f128)
==3342==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3342==    by 0x4B11AC2: start_thread (pthread_create.c:442)
==3342==    by 0x4BA2A03: clone (clone.S:100)
==3342== 
==3342== Use --history-level=approx or =none to gain increased speed, at
==3342== the cost of reduced accuracy of conflicting-access information
==3342== For lists of detected and suppressed errors, rerun with: -s
==3342== ERROR SUMMARY: 10000000 errors from 24 contexts (suppressed: 10314 from 51)
```
## mandelbrot-ld

<details>
<summary>helgrind report (before fixes)</summary>

```
==3141== Helgrind, a thread error detector
==3141== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==3141== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==3141== Command: ./mandelbrot-ld
==3141== 
==3141== ---Thread-Announcement------------------------------------------
==3141== 
==3141== Thread #1 is the program's root thread
==3141== 
==3141== ---Thread-Announcement------------------------------------------
==3141== 
==3141== Thread #17 was created
==3141==    at 0x4B589F3: clone (clone.S:76)
==3141==    by 0x4B598EE: __clone_internal (clone-internal.c:83)
==3141==    by 0x4AC76D8: create_thread (pthread_create.c:295)
==3141==    by 0x4AC81FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3141==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0xBDA1673: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD526D7: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC39FBBC: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC399D32: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC39B848: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBE07DD5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD43C19: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x25ECB3A8 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0xBDA15E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC39C4B7: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD18C: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD74F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AECC4: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3B628E: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC319143: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC314958: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC314DA1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2AC7D1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2A5AE9: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==  Address 0x25ecb3a8 is 8 bytes inside a block of size 112 alloc'd
==3141==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0xC39C49B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD18C: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD74F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AECC4: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3B628E: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC319143: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC314958: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC314DA1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2AC7D1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2A5AE9: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2A5E93: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== Possible data race during read of size 4 at 0x25ECB408 by thread #1
==3141== Locks held: none
==3141==    at 0xC39C567: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC39943D: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD3DB19: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBB5A871: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0xBB5E3FE: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0x4917792: glutSwapBuffers (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x492172A: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4922578: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141== 
==3141== This conflicts with a previous write of size 4 by thread #17
==3141== Locks held: 1, at address 0x25ECB3A8
==3141==    at 0xC39C539: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC39F06F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC39F4D3: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBDA145A: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25ecb408 is 104 bytes inside a block of size 112 alloc'd
==3141==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0xC39C49B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD18C: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD74F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AECC4: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3B628E: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC319143: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC314958: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC314DA1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2AC7D1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2A5AE9: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2A5E93: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x5046490 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0xBDA15E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC399FE8: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD3D623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3946A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3945E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD3DEEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD47265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBB5B142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0xBB60FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0xBB5C745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0xBB5D0F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==  Address 0x5046490 is 624 bytes inside a block of size 936 alloc'd
==3141==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0xC399DF6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD3D623: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3946A5: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3945E6: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD3DEEF: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBD47265: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBB5B142: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0xBB60FCF: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0xBB5C745: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0xBB5D0F7: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==3141==    by 0x4D3279A: glXChooseFBConfig (in /usr/lib/x86_64-linux-gnu/libGLX.so.0.0.0)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== Possible data race during read of size 1 at 0x25ECB3B0 by thread #1
==3141== Locks held: 1, at address 0x5046490
==3141==    at 0x485077C: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4850A2A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0xC39C500: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC39F9AC: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD6DA: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC39C75B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xBDF1216: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0x4917769: glutSwapBuffers (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x492172A: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==  Address 0x25ecb3b0 is 16 bytes inside a block of size 112 alloc'd
==3141==    at 0x484FB03: calloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0xC39C49B: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD18C: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AD74F: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3AECC4: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC3B628E: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC319143: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC314958: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC314DA1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2AC7D1: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2A5AE9: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==    by 0xC2A5E93: ??? (in /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ---Thread-Announcement------------------------------------------
==3141== 
==3141== Thread #5 was created
==3141==    at 0x4B589F3: clone (clone.S:76)
==3141==    by 0x4B598EE: __clone_internal (clone-internal.c:83)
==3141==    by 0x4AC76D8: create_thread (pthread_create.c:295)
==3141==    by 0x4AC81FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3141==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A706: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x10F1E0 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3141== 
==3141== Possible data race during write of size 4 at 0x10F010 by thread #1
==3141== Locks held: none
==3141==    at 0x10AA04: idle (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141== 
==3141== This conflicts with a previous read of size 4 by thread #5
==3141== Locks held: 1, at address 0x10F1E0
==3141==    at 0x10B45A: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3141== 
==3141== ---Thread-Announcement------------------------------------------
==3141== 
==3141== Thread #7 was created
==3141==    at 0x4B589F3: clone (clone.S:76)
==3141==    by 0x4B598EE: __clone_internal (clone-internal.c:83)
==3141==    by 0x4AC76D8: create_thread (pthread_create.c:295)
==3141==    by 0x4AC81FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3141==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A706: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x10F1E0 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3141== 
==3141== Possible data race during read of size 4 at 0x10F010 by thread #7
==3141== Locks held: 1, at address 0x10F1E0
==3141==    at 0x10B45A: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141== 
==3141== This conflicts with a previous write of size 4 by thread #1
==3141== Locks held: none
==3141==    at 0x10AA04: idle (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x10F1E0 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3141== 
==3141== Possible data race during read of size 4 at 0x10F280 by thread #7
==3141== Locks held: 1, at address 0x10F1E0
==3141==    at 0x10B464: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f280 is 0 bytes inside data symbol "h"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x10F1E0 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3141== 
==3141== Possible data race during read of size 4 at 0x10F010 by thread #7
==3141== Locks held: 1, at address 0x10F1E0
==3141==    at 0x10B482: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141== 
==3141== This conflicts with a previous write of size 4 by thread #1
==3141== Locks held: none
==3141==    at 0x10AA04: idle (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x10F1E0 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3141== 
==3141== Possible data race during read of size 4 at 0x10F280 by thread #7
==3141== Locks held: 1, at address 0x10F1E0
==3141==    at 0x10B4BA: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f280 is 0 bytes inside data symbol "h"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x10F1E0 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3141== 
==3141== Possible data race during write of size 4 at 0x10F010 by thread #7
==3141== Locks held: 1, at address 0x10F1E0
==3141==    at 0x10B496: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141== 
==3141== This conflicts with a previous write of size 4 by thread #1
==3141== Locks held: none
==3141==    at 0x10AA04: idle (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 4 at 0x10F284 by thread #7
==3141== Locks held: none
==3141==    at 0x10B225: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f284 is 0 bytes inside data symbol "w"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 8 at 0x10F290 by thread #7
==3141== Locks held: none
==3141==    at 0x10B255: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f290 is 0 bytes inside data symbol "istore"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 8 at 0x29EBB040 by thread #7
==3141== Locks held: none
==3141==    at 0x10B298: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x29ebb040 is 0 bytes inside a block of size 16,588,800 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1E2: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 4 at 0x10F280 by thread #7
==3141== Locks held: none
==3141==    at 0x10B2B0: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f280 is 0 bytes inside data symbol "h"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 4 at 0x10F014 by thread #7
==3141== Locks held: none
==3141==    at 0x10B2D7: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f014 is 0 bytes inside data symbol "iterperframe"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 8 at 0x10F298 by thread #7
==3141== Locks held: none
==3141==    at 0x10B32F: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f298 is 0 bytes inside data symbol "cstore"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 8 at 0x25F72040 by thread #7
==3141== Locks held: none
==3141==    at 0x10B339: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25f72040 is 0 bytes inside a block of size 66,355,200 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1CE: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 2 at 0x25F72048 by thread #7
==3141== Locks held: none
==3141==    at 0x10B339: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25f72048 is 8 bytes inside a block of size 66,355,200 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1CE: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 8 at 0x25F72050 by thread #7
==3141== Locks held: none
==3141==    at 0x10B33B: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25f72050 is 16 bytes inside a block of size 66,355,200 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1CE: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 2 at 0x25F72058 by thread #7
==3141== Locks held: none
==3141==    at 0x10B33B: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25f72058 is 24 bytes inside a block of size 66,355,200 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1CE: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during write of size 8 at 0x25F72040 by thread #7
==3141== Locks held: none
==3141==    at 0x10B350: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25f72040 is 0 bytes inside a block of size 66,355,200 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1CE: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during write of size 2 at 0x25F72048 by thread #7
==3141== Locks held: none
==3141==    at 0x10B350: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25f72048 is 8 bytes inside a block of size 66,355,200 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1CE: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during write of size 8 at 0x25F72050 by thread #7
==3141== Locks held: none
==3141==    at 0x10B35A: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25f72050 is 16 bytes inside a block of size 66,355,200 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1CE: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during write of size 2 at 0x25F72058 by thread #7
==3141== Locks held: none
==3141==    at 0x10B35A: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x25f72058 is 24 bytes inside a block of size 66,355,200 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1CE: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 4 at 0x10F22C by thread #7
==3141== Locks held: none
==3141==    at 0x10B373: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f22c is 0 bytes inside data symbol "iter"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during write of size 8 at 0x29EBB040 by thread #7
==3141== Locks held: none
==3141==    at 0x10B3C8: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x29ebb040 is 0 bytes inside a block of size 16,588,800 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1E2: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 8 at 0x10F288 by thread #7
==3141== Locks held: none
==3141==    at 0x10B3DA: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f288 is 0 bytes inside data symbol "tex"
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during write of size 4 at 0x2AE8E040 by thread #7
==3141== Locks held: none
==3141==    at 0x10B3E9: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x2ae8e040 is 0 bytes inside a block of size 8,294,400 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1F6: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141== Possible data race during read of size 8 at 0x29EBB590 by thread #7
==3141== Locks held: none
==3141==    at 0x10B312: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x29ebb590 is 1,360 bytes inside a block of size 16,588,800 alloc'd
==3141==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10B1E2: reshape (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x4921785: ??? (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49250C0: fgEnumWindows (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x4921CBA: glutMainLoopEvent (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x49225D2: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Block was alloc'd by thread #1
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x10F1E0 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3141== 
==3141== Possible data race during read of size 4 at 0x10F010 by thread #7
==3141== Locks held: 1, at address 0x10F1E0
==3141==    at 0x10B4B0: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141== 
==3141== This conflicts with a previous write of size 4 by thread #1
==3141== Locks held: none
==3141==    at 0x10AA04: idle (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3141== 
==3141== ---Thread-Announcement------------------------------------------
==3141== 
==3141== Thread #2 was created
==3141==    at 0x4B589F3: clone (clone.S:76)
==3141==    by 0x4B598EE: __clone_internal (clone-internal.c:83)
==3141==    by 0x4AC76D8: create_thread (pthread_create.c:295)
==3141==    by 0x4AC81FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==3141==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A706: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141== 
==3141== ----------------------------------------------------------------
==3141== 
==3141==  Lock at 0x10F1E0 was first observed
==3141==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x10A6E3: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==  Address 0x10f1e0 is 0 bytes inside data symbol "mline"
==3141== 
==3141== Possible data race during read of size 4 at 0x10F010 by thread #1
==3141== Locks held: none
==3141==    at 0x10AA15: idle (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x49225BD: glutMainLoop (in /usr/lib/x86_64-linux-gnu/libglut.so.3.9.0)
==3141==    by 0x10A7FB: main (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141== 
==3141== This conflicts with a previous write of size 4 by thread #2
==3141== Locks held: 1, at address 0x10F1E0
==3141==    at 0x10B496: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141==  Address 0x10f010 is 0 bytes inside data symbol "line"
==3141== 
==3141== 
==3141== More than 10000000 total errors detected.  I'm not reporting any more.
==3141== Final error counts will be inaccurate.  Go fix your program!
==3141== Rerun with --error-limit=no to disable this cutoff.  Note
==3141== that errors may occur in your program without prior warning from
==3141== Valgrind, because errors are no longer being displayed.
==3141== 
^C==3141== 
==3141== Process terminating with default action of signal 2 (SIGINT)
==3141==    at 0x4983E30: pow@@GLIBC_2.29 (w_pow_template.c:31)
==3141==    by 0x10AD14: color (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B3D9: renderline (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x10B4A7: trender (in /home/pasha/mandelbrot/mandelbrot-ld)
==3141==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==3141==    by 0x4AC7AC2: start_thread (pthread_create.c:442)
==3141==    by 0x4B58A03: clone (clone.S:100)
==3141== 
==3141== Use --history-level=approx or =none to gain increased speed, at
==3141== the cost of reduced accuracy of conflicting-access information
==3141== For lists of detected and suppressed errors, rerun with: -s
==3141== ERROR SUMMARY: 10000000 errors from 29 contexts (suppressed: 10319 from 55)
```
</details>



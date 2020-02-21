#!/bin/sh

gcc mandelbrot.c           -Wall -Wextra -Wno-pointer-sign -Wno-unused-parameter -march=native -O3 -lGL -lGLU -lglut -lm -lpthread            -o mandelbrot
gcc mandelbrot-ld.c        -Wall -Wextra -Wno-pointer-sign -Wno-unused-parameter -march=native -O3 -lGL -lGLU -lglut -lm -lpthread            -o mandelbrot-ld
gcc mandelbrot-f128.c      -Wall -Wextra -Wno-pointer-sign -Wno-unused-parameter -march=native -O3 -lGL -lGLU -lglut -lm -lpthread -lquadmath -o mandelbrot-f128

gcc mandelbrot_render.c    -Wall -Wextra -Wno-pointer-sign -Wno-unused-parameter -march=native -O3                   -lm -lpthread            -o mandelbrot_render
gcc mandelbrot_render-ld.c -Wall -Wextra -Wno-pointer-sign -Wno-unused-parameter -march=native -O3                   -lm -lpthread            -o mandelbrot_render-ld


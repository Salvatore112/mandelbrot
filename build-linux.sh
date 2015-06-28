#!/bin/sh

gcc mandelbrot.c -Wall -Wextra -march=native -O3 -lGL -lGLU -lglut -lm -lpthread -o mandelbrot

gcc mandelbrot_headless.c -Wall -Wextra -march=native -O3 -lm -lpthread -o mandelbrot_headless


#!/bin/sh

gcc mandelbrot.c -Wall -Wextra -march=native -O3 -lGL -lGLU -lglut -lm -lpthread -o mandelbrot

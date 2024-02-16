#!/bin/bash
set -xe

gcc  -lm -Wall -Wextra -D CORRER=1 -o main plots.c ../AlgebraLineal/vectores.o
./main

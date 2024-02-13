#!/bin/bash
set -xe

gcc -std=c11 -lm -Wall -Wextra -D CORRER=1 -o main vectores.c

./main

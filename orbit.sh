#!/bin/bash
g++ -g -o $1 $2 videogen.h getiniExp.h ProgressBar.hpp `pkg-config --cflags --libs plplot-c++ armadillo jsoncpp opencv`


#!/bin/bash
g++ -g -o $1 $2 videogen.h getiniExp.h `pkg-config --cflags --libs plplot-c++ armadillo jsoncpp opencv`


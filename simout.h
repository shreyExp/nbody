#ifndef SIMOUT_H
#define SIMOUT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "ProgressBar.hpp"

using namespace std;
using namespace cv;

void makeCircle(cv::Mat &m);
void minmax(double *x, double &m, double &ma, int iter);
void minmax2d(double **x, int nbodies, int iter, double &m, double &ma);
void generateVideo(double **x, double **y, int iter, int nbodies, int duration, string filename);

#endif

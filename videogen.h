#ifndef VIDEOGEN_H
#define VIDEOGEN_H

void makeCircle(cv::Mat &m);
void minmax(double *x, double &m, double &ma, int iter);
void minmax2d(double **x, int nbodies, int iter, double &m, double &ma);
void videoGen(double **x, double** y, int nbodies, int iter, int duration, string filename);

#endif

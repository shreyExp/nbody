#ifndef SIMOUT_H
#define SIMOUT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "ProgressBar.hpp"

using namespace std;
using namespace cv;
class Simout{
	public:
		double **x;
		double **y;
		int nbodies;
		int iter;
		int duration;
		std::string filename;
		void makeCircle(cv::Mat &m);
		void minmax(double *x, double &m, double &ma, int iter);
		void minmax2d(double **x, int nbodies, int iter, double &m, double &ma);
		void videoGen();
};

#endif

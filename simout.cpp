#include "simout.h"
#include <opencv2/videoio.hpp>

void minmax(double *x, double &m, double &ma, int iter);
void minmax2d(double **x, int iter, int nbodies, double &m, double &ma);
void generateVideo(double **x, double **y, int iter, int nbodies, int duration, string filename);

void generateVideo(double **x, double **y, int iter, int nbodies, int duration, string filename){
	int imgDimension = 1000;
	Size S(imgDimension, imgDimension);
	cv::Mat im(imgDimension, imgDimension, CV_8UC1);
	const double fps = 60;
	const int stepSize = iter/(fps * duration);
	cout<<"num bodies in the simout is "<<nbodies<<endl;
	//for(int i = 0; i < 10; i++)
	//	for(int j = 0; j < nbodies; j++)
	//		cout<<"x is "<<x[i][j]<<endl;
	double xmin, xmax, ymin, ymax;
	minmax2d(x, iter, nbodies, xmin, xmax);
	minmax2d(y, iter, nbodies, ymin, ymax);
	cout<<"xmax is: "<<xmax<<"xmin: "<<xmin<<endl;
	cout<<"ymax is: "<<ymax<<"ymin: "<<ymin<<endl;

	//double maxout = 4.09992e+06;
	//double minout = 0.500003;
	//for(int i = 0; i < iter; i++)
	//	for(int j = 0; j < nbodies; j++){
	//		if (x[i][j] > maxout)
	//			cout<<"Greater than Value of x["<<i<<"]["<<j<<"] = "<<x[i][j]<<endl;
	//		if (x[i][j] < minout)
	//			cout<<"Min than Value of x["<<i<<"]["<<j<<"] = "<<x[i][j]<<endl;
	//	}

	
	
	if (xmin < 0){
		for(int i=0; i<iter; i++){ 
			for(int j = 0; j < nbodies; j++){
				x[i][j] = x[i][j] - xmin;	
			}
		}
	}

	if (ymin < 0){
		for(int i=0; i<iter; i++){
			for(int j = 0; j < nbodies; j++){
				y[i][j] = y[i][j] - ymin;	
			}
		}
	}

	double xcomp[4] = {xmin, xmax, ymin, ymax};
	double min, max;
	minmax(xcomp, min, max, 4); 
	double bodySize = 30.0;	
	double sideBuffer = 4 * bodySize;
	double simWidth = imgDimension - sideBuffer;
	double xscale = simWidth/(max - min);
	double yscale = simWidth/(max - min);
	
	cv::VideoWriter vid(filename, cv::VideoWriter::fourcc('P','I','M','1'), fps, S, false);
	int bodySizeInt;
	bodySizeInt = bodySize;
	cv::Mat body(bodySizeInt, bodySizeInt, CV_8UC1);
	makeCircle(body);
	im = Scalar(0);
	int k,l;

	double shiftx, shifty;
	shiftx = (imgDimension - (xmax - xmin) * xscale)/2;
	shifty = (imgDimension - (ymax - ymin) * yscale)/2;

	cout<<"\n\nWriting the output..."<<endl;
	ProgressBar progressBar(iter/stepSize, 70, '=', '-');
	for(int i = 0; i < iter; i = i + stepSize){
		for(int j = 0; j < nbodies; j = j + 1){
			k = x[i][j] * xscale + shiftx;		
			l = y[i][j] * yscale + shifty;

			body.copyTo(im(Rect(k,(1000 - l), body.cols, body.rows)));	
		}
		vid<<im;
		im = Scalar(0);
		++progressBar;
		if(i % 10 == 0)
			progressBar.display();
	}
	cout<<"\nOutput written!\nProgram finished"<<endl;
	progressBar.done();
}
void minmax(double *x, double &m, double &ma, int iter){
	double min, max;
	min = x[0];
	max = x[0];
	for(int i = 0; i < iter; i++){
		if(x[i] < min)
			min = x[i];
		if(x[i] > max)
			max = x[i];	
	}
	m = min;
	ma = max;
//	cout<<"Minimum is "<<min<<endl;
//	cout<<"Maximum is "<<max<<endl;
}

void minmax2d(double **x, int iter, int nbodies, double &m, double &ma){
	double xmax = x[0][0];
	double xmin = x[0][0];
	for(int i = 0; i < iter; i++)
		for(int j = 0; j < nbodies; j++){
			if(xmax < x[i][j]){
				xmax = x[i][j];
			}
			if(xmin > x[i][j]){
				xmin = x[i][j];
			}
		}
	m = xmin;
	ma = xmax;
	cout<<"Max is "<<ma<<endl;
	cout<<"Min is "<<m<<endl;
}
void makeCircle(cv::Mat &m){
//	int ch  = m.channels();	
	int nrows = m.rows;
	int ncols = m.cols;
//	ncols *= ch;
	uchar *p;
//	int sfCol = 0;
	for(int i = 0; i < nrows; i++){
			p = m.ptr<uchar>(i);
//			for(int j = 0; j < ncols; j += ch){
			for(int j = 0; j < ncols; j++){
				if((pow((j - nrows/2), 2) + pow((i - nrows/2), 2)) <= pow((nrows/2), 2))
					p[j] = 255;
				else
					p[j] = 0;
//				sfCol++;
//				cout<<"i = "<<i<<"j = "<<j<<"P["<<i<<","<<j<<"]"<<p[j]<<endl;
			}
	}
}

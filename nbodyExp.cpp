#include <iostream> 
#include "math.h"
#include <armadillo>
#include <string>
#include "getini.h"
#include <sstream>
#include "videogen.h"
#include "ProgressBar.hpp"
using namespace arma; //To  use anmadillo objects
using namespace std;
inline Col<double> acc(Col<double> , Col<double> , double );
int main(int argc, char** argv){
	string f;
	if (argc>1){
		f = argv[1];  
	}else{
		f = "parameters.json";
	}
	const char* fi = f.c_str();
	GetIni ini(fi);
	double *mass,  **x, **y;
	const int nbodies = ini.nOfBodies();
	const int iter = ini.getIteration();
	const double h = ini.getIterStepSize();
	Col<double> xa; 
	ini.getXprojection(xa);// to be written
	Col<double> ya; 
	ini.getYprojection(ya);// to be written
	ini.getMass(mass); //to be written
	Col<double> *R;
	Col<double> *v;
	Col<double> a[nbodies];

	ini.getPositions(R);
	ini.getVelocities(v);
	y = new double*[nbodies];
	x = new double*[nbodies];
	for(int l = 0; l < nbodies; l++){
		y[l] = new double[iter];
		x[l] = new double[iter];
	}

	ProgressBar progressBar(iter, 70, '#', '-');

	cout<<"Iterating....."<<endl;
	for(int k = 0; k < iter; k++){
		for(int j = 0; j < nbodies; j++){//This can be parallelized
			a[j]<<0<<0<<0; //To stop accumulation : a should be new for new calculation
			for(int i = 0; i < nbodies; i++){
				if(i == j){
					continue;
				}
				a[j] += acc(R[j],R[i], mass[i]);
			}
			v[j] = v[j] + h*a[j];
			R[j] = R[j] + h*v[j];
			x[j][k] = dot(R[j], xa);
			y[j][k] = dot(R[j], ya);
		}
		++progressBar;
		if(k % 10 == 0)
			progressBar.display();
	}
	cout<<"Iterating Complete.";
	string fileName = ini.getVideoFileName();
	int duration = ini.getVideoDuration();
	videoGen(x, y, nbodies, iter, duration, fileName);
//	displayer(x[0], y[0], x[1], y[1], iter, duration, fileName);
}
inline Col<double> acc(Col<double> R1, Col<double> R2, double m){
	double G = 6.67408e-20;
	Col<double> a = (G*m/pow((norm(R2-R1)),3))*(R2-R1); 	
	return a;
}

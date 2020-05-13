#include <iostream> 
#include "math.h"
#include <armadillo>
#include <string>
#include "getini.h"
#include <sstream>
#include "simout.h"
#include "ProgressBar.hpp"
using namespace arma; //To  use anmadillo objects
using namespace std;
void minmax(double**, int, int);
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
	ini.getYprojection(ya);// to be edited
	ini.getMass(mass); //to be written
	Col<double> *R;
	Col<double> *v;
	Col<double> a[nbodies];

	ini.getPositions(R);
	ini.getVelocities(v);
	x = new double*[iter];
	y = new double*[iter];
	for(int l = 0; l < iter; l++){
		x[l] = new double[nbodies];
		y[l] = new double[nbodies];
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
			x[k][j] = dot(R[j], xa);
			y[k][j] = dot(R[j], ya);
			//cout<<"x"<<"["<<k<<"]"<<"["<<j<<"]"<<"= "<<x[k][j]<<endl;
			//cout<<"y"<<"["<<k<<"]"<<"["<<j<<"]"<<"= "<<y[k][j]<<endl;
		}
		++progressBar;
		if(k % 10 == 0)
			progressBar.display();
	}
	//for(int i = 0; i < 10; i++)
	//	for(int j = 0; j < nbodies; j++)
	//		cout<<"x["<<i<<"]["<<j<<"] = "<<x[i][j]<<endl;

	cout<<"Iterating Complete.";
	string filename = ini.getVideoFileName();
	int duration = ini.getVideoDuration();
	//minmax(x, nbodies, iter);
	//Simout vid;
	//vid.x = x;
	//vid.y = y;
	//vid.nbodies = nbodies;
	//vid.iter = iter;
	//vid.duration = duration;
	//vid.filename = filename;
	//vid.videoGen();
	//cout<<" Number of bodies in the ,ain program: "<<nbodies<<endl;
	generateVideo(x, y, iter, nbodies, duration, filename);
}
inline Col<double> acc(Col<double> R1, Col<double> R2, double m){
	double G = 6.67408e-20;
	//double G = 6.67408e-7;
	Col<double> a = (G*m/pow((norm(R2-R1)),3))*(R2-R1); 	
	return a;
}
void minmax(double **x, int nbodies, int iter){
	double xmax = x[0][0];
	double xmin = x[0][0];
	for(int i = 0; i < iter; i++){
		for(int j = 0; j < nbodies; j++){
			if(xmax < x[i][j]){
				xmax = x[i][j];
			}
			if(xmin > x[i][j]){
				xmin = x[i][j];
			}
		}
	}
	cout<<"Max is"<<xmax<<endl;
	cout<<"Min is"<<xmin<<endl;

}


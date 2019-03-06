#ifndef GETINI_H
#define GETINI_H

#include <fstream>
#include <string>
#include <json/json.h>
#include <iostream>
#include <armadillo>
using namespace Json;
using namespace std;
using namespace arma;
class GetIni{
	public:
		GetIni(const char *);
		int nOfBodies();
		int getIteration();
		double getIterStepSize();
		void getXprojection(Col<double> &);
		void getYprojection(Col<double> &);
		void getPositions(Col<double> * &);
		void getVelocities(Col<double> * &);
		int getVideoDuration();
		string getVideoFileName();
		void getMass(double * &);
	private:
		const char *filename;
		Value root;
		int numbodies;
		int iterations;
		double stepsize;
};

#endif

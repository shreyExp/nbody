#include "getini.h"
GetIni::GetIni(const char* name){
	filename = name;	
	ifstream in;
	in.open(filename);
	in>>root;
	numbodies = root["numbodies"].asInt(); 
	
}

int GetIni::nOfBodies(){
	return root["numbodies"].asInt();
}

int GetIni::getIteration(){
	return root["iterations"].asInt();
}
double GetIni::getIterStepSize(){
	return root["stepsize"].asDouble();
}

void GetIni::getPositions(Col<double> * &R){
	R = new Col<double>[numbodies];
	Value sub;
	for(int i = 0; i < numbodies; i++){
		sub = root["bodies"][i]["initialposition"];
		R[i] << sub[0].asDouble()<<sub[1].asDouble()<<sub[2].asDouble();
	}
}

void GetIni::getVelocities(Col<double> * &v){
	v = new Col<double>[numbodies];
	Value sub;
	for(int i = 0; i < numbodies; i++){
		sub = root["bodies"][i]["initialvelocity"];
		v[i] << sub[0].asDouble()<<sub[1].asDouble()<<sub[2].asDouble();
	}
}

string GetIni::getVideoFileName(){
	return root["videofilename"].asString();
}

int GetIni::getVideoDuration(){
	return root["videoduration"].asInt();
}

void GetIni::getXprojection(Col<double> &x){
		Value sub = root["xprojection"];
		x << sub[0].asDouble()<<sub[1].asDouble()<<sub[2].asDouble();
}

void GetIni::getYprojection(Col<double> &y){
		Value sub = root["yprojection"];
		y << sub[0].asDouble()<< sub[1].asDouble()<< sub[2].asDouble();
}

void GetIni::getMass(double * &mass){
	mass = new double[numbodies];
	for(int i = 0; i < numbodies; i++){
			mass[i] = root["bodies"][i]["mass"].asDouble();
	}
}

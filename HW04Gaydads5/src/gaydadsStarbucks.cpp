#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "gaydadsStarbucks.h"
#include <fstream>
#include <cstdlib>
#include <math.h>
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

node::node(){
	left = NULL;
	right = NULL;
	data = NULL;
}

node::node(Entry* entry){
	left = NULL;
	right = NULL;
	data = entry;
}

gaydadsStarbucks::gaydadsStarbucks(){
}


void gaydadsStarbucks::randomize(Entry* locations, int n){
	int x = 0;
	int tempn = n;

	for(int i=0; i<n; i++){
		int random = rand()%tempn + 1;
		Entry temp = locations[random];
		locations[random] = locations[tempn];
		locations[tempn] = temp;
		tempn = tempn - 1;
	}
}



void gaydadsStarbucks::build(Entry* c, int n){
	//Array
	Locations = new Entry[n];
for (int i=0; i<n; i++){
	Locations[i] = c[i];
}
}



Entry* gaydadsStarbucks::getNearest(double x, double y){
	//Array
	
	double distance = abs(sqrt(   ((x-Locations[0].x)*(x-Locations[0].x)) + ((y-Locations[0].y)*(y-Locations[0].y))));;
	Entry* temp = &(Locations[0]);

	for(int i=1; i<7655; i++ ){
		double distance2 = abs(sqrt(   ((x-Locations[i].x)*(x-Locations[i].x)) + ((y-Locations[i].y)*(y-Locations[i].y))));
		if (distance > distance2) {
			distance = distance2;
			temp = &(Locations[i]);
		}
	}

	Entry* nearest = temp;
	return nearest;





}
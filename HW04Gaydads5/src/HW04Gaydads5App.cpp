#pragma once
#include "Resources.h"
#include "Image.h"
#include "cinder/ImageIo.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "HW04Gaydads5App.h"
#include "Starbucks.h"
#include "gaydadsStarbucks.h"
#include "cinder/Rand.h"
#include <fstream>
#include <cstdlib>

using namespace ci;
using namespace ci::app;
using namespace std;

/**
*Read in Starbucks locations
*
**/
Entry* HW04Gaydads5App::readFile(){
	string line;
	double x, y;
	ifstream myFile("Starbucks_2006.csv");
	int numItems = 7655;
	

	Entry* arr = new Entry[numItems];
	for(int i = 0; i < numItems; i++){
		getline(myFile, line, ',');
		arr[i].identifier = line;
		getline(myFile, line, ',');
		x = atof(line.c_str());
		arr[i].x = x;
		getline(myFile, line, '\r');
		y = atof(line.c_str());
		arr[i].y = y;
	}
	ifstream myfile("Starbucks_2006.csv");
	return arr;
}

/**
*Read in Census 2000 data
*
**/
CensusEntry* HW04Gaydads5App::readcensus2000() {

	double x=0;
	double y = 0;
	int StateID=0;
	int population = 0;
	state_pop_2000 = new int [56];
	int popcount = 0;
	string line;
	//2000
	CensusEntry* arr2000 = new CensusEntry[206676];
	ifstream myFile("Census_2000.csv");
	for(int i = 0; i < 206676; i++){
		getline(myFile, line, ',');
		StateID = atof(line.c_str());
		arr2000[i].stateID = StateID; //Skip 4 lines
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		population = atof(line.c_str());
		arr2000[i].population=population;
		popcount = population + popcount;
		state_pop_2000[1] = popcount;
		getline(myFile, line, ',');
		x = atof(line.c_str());
		arr2000[i].x = x;
		getline(myFile, line, '\r');
		y = atof(line.c_str());
		arr2000[i].y = y;
	}
	return arr2000;
}
  
/**
*Read in Census 2010 data
*
**/
CensusEntry* HW04Gaydads5App::readcensus2010() {
	ifstream myFile("Census_2010.csv");
	double x=0;
	double y = 0;
	int StateID=0;
	int population = 0;
	int popcount = 0;
	
	state_pop_2010 = new int [56];
	string line;
	//2010
	CensusEntry* arr2010 = new CensusEntry[2216331];
	for(int i = 0; i < 216331; i++) {
		getline(myFile, line, ',');
		StateID = atof(line.c_str());
		arr2010[i].stateID = StateID; //Skip 4 lines
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		population = atof(line.c_str());
		arr2010[i].population=population;
		popcount = population + popcount;
		state_pop_2010[1] = popcount;
		getline(myFile, line, ',');
		x = atof(line.c_str());
		arr2010[i].x = x;
		getline(myFile, line, '\r');
		y = atof(line.c_str());
		arr2010[i].y = y;
	}
	return arr2010;
}

void HW04Gaydads5App::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(windowWidth,windowHeight);
	(*settings).setResizable(false);
}

void HW04Gaydads5App::setup() {
	toggle = 0;
	mySurface = new Surface(1024,1024,false);
	Surface myImage;
	myImage = loadImage("NewMap.jpg");
	*mySurface = myImage;
	dataArray = (*mySurface).getData();
	zoomSurf = new Surface(1024,1024,true);
	zoomPix = (*zoomSurf).getData();
	zoomConst = 1;
	yOffset = 0;
	xOffset = 0;

	myTexture = new gl::Texture(*mySurface);
	structure = new gaydadsStarbucks();
	Entry* AllStarbucks = readFile();
	
	structure->build(AllStarbucks,7655);
	Starbucks = AllStarbucks;
	arr2000 = readcensus2000();
	arr2010 = readcensus2010();
	/*int count = 0;
	int col=0;
	int diff = 0;
	for (int i =0; i<206676; i++) {
		if (count == 10) {
			count = 0;
		diff = arr2010[i].population-arr2000[i].population;
	
		structure->getNearest(arr2010[i].x,arr2010[i].y);
		int xcor = arr2010[i].x*800;
		int ycor = (1-arr2010[i].y)*600;
		int j = 3*(xcor+ycor*800);
		Color8u color;
		if (diff < 0) {
			col = diff*255/-26815;
			color = Color8u(col+100,0,0);
			dataArray[j] = color.r;
			dataArray[j+1] = color.g;
			dataArray[j+2] = color.b;
		}
		else if (diff == 0) {
			color = Color8u(255,255,0);
			dataArray[j] = color.r;
			dataArray[j+1] = color.g;
			dataArray[j+2] = color.b;
		}
		else{
			col = diff*255/15973;
			color = Color8u(0,col+100,0);
			dataArray[j] = color.r;
			dataArray[j+1] = color.g;
			dataArray[j+2] = color.b;
		}
	}
		count++;
	}*/

	//Plot starbucks locations
	Color8u color2;
	for(int i = 0; i < 7655; i++){
		color2.r = rand()*255;
		color2.g = rand()*255;
		color2.b = rand()*255;
		int xcor = Starbucks[i].x*800;
		int ycor = (1-Starbucks[i].y)*600;

		int j = 3*(xcor+ycor*800);

	dataArray = (*mySurface).getData();
		dataArray[j] = color2.r;
		dataArray[j+1] = color2.g;
		dataArray[j+2] = color2.b;
	}
	

	/*int xcor,ycor,j;
	count = 0;
	for (double y=0; y<600; y++) {
	for (double x=0; x<800; x++) {
			if((int)x%5==0) {
				if((int)y%5==0) {
			location = structure->getNearest(x/800,y/600);
			xcor = location->x*800;
			ycor = (1-location->y)*600;
			j = 3*(xcor+ycor*800);

			int index = 3*(x+y*800);
			Color8u color;
			color.r = dataArray[j];
			color.g = dataArray[j+1];
			color.b = dataArray[j+2];

			dataArray[index] = color.r;
			dataArray[index+1] = color.g;
			dataArray[index+2] = color.b;
			console() << "Working..."<<endl;
				}
			}
		}
	}*/
}

void HW04Gaydads5App::mouseDown( MouseEvent event )
{
	clicked = true;
	if(event.isLeft()){
		mouse_x = event.getX();
		mouse_y = event.getY();
	}
}

void HW04Gaydads5App::keyDown( KeyEvent event) {
	if (event.getCode() ==KeyEvent::KEY_SPACE) {
		toggle++;
		if (toggle == 3) {
			toggle = 0;
		}
	}
}

void HW04Gaydads5App::update()
{
	dataArray = (*mySurface).getData();
	(*myTexture).update(*mySurface,(*mySurface).getBounds());
}

void HW04Gaydads5App::draw()
{
	
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	//Draw Map
	gl::draw(*myTexture);
	//Plot population trend points
	if (toggle == 1) {
	int count = 0;
	int col=0;
	int diff = 0;
	for (int i =0; i<206676; i++) {
		if (count == 100) {
			count = 0;
		diff = arr2010[i].population-arr2000[i].population;
	
		structure->getNearest(arr2010[i].x,arr2010[i].y);
		int xcor = arr2010[i].x*800;
		int ycor = (1-arr2010[i].y)*600;
		int j = 3*(xcor+ycor*800);
		Color8u color;
		if (diff < 0) {
			col = diff*255/-26815;
			color = Color8u(col+100,0,0);
			dataArray[j] = color.r;
			dataArray[j+1] = color.g;
			dataArray[j+2] = color.b;
		}
		else if (diff == 0) {
			color = Color8u(255,255,0);
			dataArray[j] = color.r;
			dataArray[j+1] = color.g;
			dataArray[j+2] = color.b;
		}
		else{
			col = diff*255/15973;
			color = Color8u(0,col+100,0);
			dataArray[j] = color.r;
			dataArray[j+1] = color.g;
			dataArray[j+2] = color.b;
		}
	}
		count++;
		console() << "Hold..."<<endl;
	}

	}

	/*if (toggle == 2) {
	int xcor,ycor,j;
	for (double y=0; y<600; y++) {
	for (double x=0; x<800; x++) {
			if((int)x%5==0) {
				if((int)y%5==0) {
			location = structure->getNearest(x/800,y/600);
			xcor = location->x*800;
			ycor = (1-location->y)*600;
			j = 3*(xcor+ycor*800);

			int index = 3*(x+y*800);
			Color8u color;
			color.r = dataArray[j];
			color.g = dataArray[j+1];
			color.b = dataArray[j+2];

			dataArray[index] = color.r;
			dataArray[index+1] = color.g;
			dataArray[index+2] = color.b;
			console() << "Working..."<<endl;
				}
			}
		}
	}
	}*/

	if (clicked == true) {
		double x = mouse_x/800;
		double y = 1- (mouse_y/600);
		
	Entry*	location = structure->getNearest(x,y);
	
	gl::drawSolidCircle(Vec2f (((location->x*800)), (((1-location->y)*600)) ), 2.0f);
	
	}
}

CINDER_APP_BASIC( HW04Gaydads5App, RendererGl )

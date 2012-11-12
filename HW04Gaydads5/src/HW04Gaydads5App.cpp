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

StarbucksColor* HW04Gaydads5App::getNearest(double x, double y){
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
		arr2000[i].stateID = StateID;
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		population = atof(line.c_str());
		popcount = population + popcount;
		state_pop_2000[1] = popcount;
		getline(myFile, line, ',');
		x = atof(line.c_str());
		arr2000[i].x = x;
		getline(myFile, line, '\r');
		y = atof(line.c_str());
		arr2000[i].y = y;
	}

	console() << "StateID 1 2000:" << state_pop_2000[1]<<endl;
	return arr2000;
}
  
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
		arr2010[i].stateID = StateID;
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		population = atof(line.c_str());
		popcount = population + popcount;
		state_pop_2010[1] = popcount;
		getline(myFile, line, ',');
		x = atof(line.c_str());
		arr2010[i].x = x;
		getline(myFile, line, '\r');
		y = atof(line.c_str());
		arr2010[i].y = y;
	}
	

	console() << "StateID 1 2010:" << state_pop_2010[1]<<endl;
	return arr2010;
}

void HW04Gaydads5App::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(windowWidth,windowHeight);
	(*settings).setResizable(false);
}

void HW04Gaydads5App::setup() {
	//gl::Texture myTexture; // initialized elsewhere

	////////
	mySurface_ = new Surface(1024,1024,true);
	mySurface_->hasAlpha();
	//gl::enableAlphaBlending;
	uint8_t* dataArray = (*mySurface_).getData();
	Color8u color;
	for(int y=0; y<=800; y++){
		for(int x=0;x<=800; x++){

			int i = 4*(x + y*800);
			
			dataArray[i] = 255;
			dataArray[i+1] = 255;
			dataArray[i+2] = 255;
			dataArray[i+3] = 1.0;
		}
	}
	myTexture = new gl::Texture(*mySurface_);
	myImage= (gl::Texture( loadImage( loadResource( RES_IMAGE, "IMAGE" ) ) ));
	myTexture = &(gl::Texture( loadImage( loadResource( RES_IMAGE, "IMAGE" ) ) ));
	structure = new gaydadsStarbucks();
	Entry* AllStarbucks = readFile();
	//Entry* location;
	
	structure->build(AllStarbucks,7655);
	
	//location = structure->getNearest(.5,.5);
	//HW04Gaydads5App::console() <<location->identifier <<std::endl;
	Starbucks = AllStarbucks;

	readcensus2000();
	arr2010 = readcensus2010();
		/*for(int i = 0; i < 216331; i++){ 
		for (int j = 1; j<57; j++) {

		if (arr2010[i].stateID == j) {
			gl::drawSolidCircle( Vec2f (((arr2010[i].x*800)), (((1-arr2010[i].y)*600)) ), 2.0f);
			}
		}
	}*/
	console() <<"State 1 pop: " << state_pop_2010[1] - state_pop_2000[1] <<endl;
}

void HW04Gaydads5App::mouseDown( MouseEvent event )
{
	clicked = true;
	if(event.isLeft()){
		mouse_x = event.getX();
		mouse_y = event.getY();

		//console() << "clicked!" <<endl;
	}
}

void HW04Gaydads5App::update()
{
	//uint8_t* dataArray = (*mySurface_).getData();
	//(*myTexture).update(*mySurface_,(*mySurface_).getBounds());
}

void HW04Gaydads5App::draw()
{
	
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::draw( myImage, getWindowBounds() );
	gl::drawSolidCircle( Vec2f( 575.0f, 175.0f ), 5.0f  );

	Color8u color2;
	StarbucksColor* sc = new StarbucksColor[7655];
	for(int i = 0; i < 7655; i++){
		color2.r = rand()*255;
		color2.g = rand()*255;
		color2.b = rand()*255;

		gl::drawSolidCircle( Vec2f( Starbucks[i].x*800, (1-Starbucks[i].y)*600) , 1.0f);
		sc[i].color = color2;
		sc[i].x = Starbucks[i].x;
		sc[i].y = Starbucks[i].y;
		sc[i].identifier = Starbucks[i].identifier;

		gl::color(255,255,255);
		/*if (Starbucks[i].x >=.5) {

			if (Starbucks[i].y>=.5) {
				gl::drawSolidCircle( Vec2f(  (( (Starbucks[i].x*550 ) - (Starbucks[i].y*(375)/10)  +225/2 )), (Starbucks[i].y*(-400)) +520), 1.0f);
			}
			else {
			gl::drawSolidCircle( Vec2f(  (( (Starbucks[i].x*550 ) - (Starbucks[i].y*(375)/10)  +225/2 )), (Starbucks[i].y*(-400))+520), 1.0f);
			}
		}
		else {
			if (Starbucks[i].y>=.5) {

			}
		gl::drawSolidCircle( Vec2f(  (( (Starbucks[i].x *550) + (Starbucks[i].y*(375)/10) )), (Starbucks[i].y*(-400))+520), 1.0f);
		}*/
	}

	if (clicked == true) {
		double x = mouse_x/800;
		double y = 1- (mouse_y/600);
		//console() << x<< " " << y <<endl;
	//console() << location->identifier<< "X=" << location->x <<"Y="  << location->y <<endl;
	Entry*	location = structure->getNearest(x,y);
	gl::color(0,0,255);
	gl::drawSolidCircle( Vec2f (((location->x*800)), (((1-location->y)*600)) ), 2.0f);
	gl::color(255,255,255);
	}
	Entry* locs = new Entry[600*800];
	for (int i = 0; i<600; i++) {
		for (int j =0; j<800; j++) {
			StarbucksColor* loc = structure->getNearest(j/800,1-(i/800));
			
			gl::drawSolidCircle( Vec2f (i, j ), 1.0f);
		}
	}
	/*for(int i = 0; i < 216331; i++){ 
		for (int j = 1; j<57; j++) {

		if (arr2010[i].stateID == j) {
			gl::drawSolidCircle( Vec2f (((arr2010[i].x*800)), (((1-arr2010[i].y)*600)) ), 2.0f);
			}
		}
	}*/

	/*
	//west = 25
	//east = 575
	//550
	//north = 115
	//south = 490
	//375
	//x = (latitude - 24)/(49-24)

    //y = (longitude - (-125))/((-63) - (-125))

	//x = (latitude - 24)/(49-24)

//y = (longitude - (-125))/((-63) - (-125))

	
*/
	//gl::draw(*myTexture);
}

CINDER_APP_BASIC( HW04Gaydads5App, RendererGl )

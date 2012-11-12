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
	mySurface = new Surface(1024,1024,false);
	Surface myImage;
	myImage = loadImage("NewMap.jpg");
	*mySurface = myImage;
	
	//(gl::Texture( loadImage( loadResource( RES_IMAGE, "IMAGE" ) ) ));
	dataArray = (*mySurface).getData();
	zoomSurf = new Surface(1024,1024,true);
	zoomPix = (*zoomSurf).getData();
	zoomConst = 1;
	yOffset = 0;
	xOffset = 0;


	//Color8u color;


	myTexture = new gl::Texture(*mySurface);
	/*myImage= (gl::Texture( loadImage( loadResource( RES_IMAGE, "IMAGE" ) ) ));
	myTexture = &(gl::Texture( loadImage( loadResource( RES_IMAGE, "IMAGE" ) ) ));
	*/
	structure = new gaydadsStarbucks();
	Entry* AllStarbucks = readFile();
	Entry* location;
	
	structure->build(AllStarbucks,7655);
	
	//location = structure->getNearest(.5,.5);
	//HW04Gaydads5App::console() <<location->identifier <<std::endl;
	Starbucks = AllStarbucks;

	//readcensus2000();
	//arr2010 = readcensus2010();
	Color8u color2;
	for(int i = 0; i < 7655; i++){
		color2.r = rand()*255;
		color2.g = rand()*255;
		color2.b = rand()*255;
		int xcor = Starbucks[i].x*800;
		int ycor = (1-Starbucks[i].y)*600;

		//Color8u color(255,255,255);
		int j = 3*(xcor+ycor*800);

	dataArray = (*mySurface).getData();
	//Color8u color = Color8u(255,255,255);
		dataArray[j] = color2.r;
		dataArray[j+1] = color2.g;
		dataArray[j+2] = color2.b;
	}
	/*int x=0;
	int y=0;
	for (int i=0; i<800*600; i++) {
		if (x%800 == 0) {
			x=0;
			y++;
		}
		x++;
		if(i%30==0) {
		*/
	int xcor,ycor,j;
	int count = 0;
	for (double y=0; y<600; y++) {
	for (double x=0; x<800; x++) {
		//if (count == 100) {
			//count = 0;
			if((int)x%5==0) {
				if((int)y%5==0) {
			location = structure->getNearest(x/800,y/600); //x/800,y/600
			console() << location->identifier<<endl;
			xcor = location->x*800;
			ycor = (1-location->y)*600;
			j = 3*(xcor+ycor*800);

			//dataArray = (*mySurface).getData();

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
		//count++;
			}
		}
	}
		/*for(int i = 0; i < 216331; i++){ 
		for (int j = 1; j<57; j++) {

		if (arr2010[i].stateID == j) {
			gl::drawSolidCircle( Vec2f (((arr2010[i].x*800)), (((1-arr2010[i].y)*600)) ), 2.0f);
			}
		}
	}*/
	//console() <<"State 1 pop: " << state_pop_2010[1] - state_pop_2000[1] <<endl;
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
	dataArray = (*mySurface).getData();
	(*myTexture).update(*mySurface,(*mySurface).getBounds());
}

void HW04Gaydads5App::draw()
{
	
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	
	//gl::draw( myImage, getWindowBounds() );
	//gl::drawSolidCircle( Vec2f( 575.0f, 175.0f ), 5.0f  );

	/*Color8u color2;
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
		*/
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
		}
	}*/
	gl::draw(*myTexture);
	if (clicked == true) {
		double x = mouse_x/800;
		double y = 1- (mouse_y/600);
		//console() << x<< " " << y <<endl;
	//console() << location->identifier<< "X=" << location->x <<"Y="  << location->y <<endl;
	Entry*	location = structure->getNearest(x,y);
	
	/*for(int y=0; y<800; y++){
		for(int x=0;x<600; x++){
			if(y < 0 || x < 0) continue;

			//If correct distance away from mid points
			if ((pow(x-location->x*600,2) + (pow(y-(1-location->y)*800,2))) <= (pow(50.0,2))) {
			int i = 3*(x + y*800);
			Color8u color = Color8u(255,255,255);
			dataArray[i] = color.r;
			dataArray[i+1] = color.g;
			dataArray[i+2] = color.b;
			}
		}
		}
	}*/
	//gl::Texture().
	gl::drawSolidCircle(Vec2f (((location->x*800)), (((1-location->y)*600)) ), 2.0f);
	//myTexture = new gl::Texture(*mySurface);
	//gl::drawSolidCircle(Vec2f (((location->x*800)), (((1-location->y)*600)) ), 10.0f);
	//gl::color(0,0,255);
	//gl::drawSolidCircle( Vec2f (((location->x*800)), (((1-location->y)*600)) ), 2.0f);
	//gl::color(255,255,255);
	}
	/*Entry* locs = new Entry[600*800];
	for (int i = 0; i<600; i++) {
		for (int j =0; j<800; j++) {
			StarbucksColor* loc = structure->getNearest(j/800,1-(i/800));
			
			gl::drawSolidCircle( Vec2f (i, j ), 1.0f);
		}
	}*/
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

	//Entry* Starbucks = readFile();
	//for(int i = 0; i < 7655; i++){
		/*color2.r = rand()*255;
		color2.g = rand()*255;
		color2.b = rand()*255;*/
		/*int xcor = Starbucks[i].x*1024;
		int ycor = (1-Starbucks[i].y)*1024;
		Color8u color(255,255,255);
		int j = 3*(xcor+ycor*800);
		dataArray[j] = color.r;
		dataArray[j+1] = color.g;
		dataArray[j+2] = color.b;*/
	/*dataArray = (*mySurface).getData();
	Color8u color = Color8u(255,255,255);
	int j = 3*(1);
		dataArray[j] = color.r;
		dataArray[j+1] = color.g;
		dataArray[j+2] = color.b;
		*/
		/*for (int x=0; x<600; x++) {
			for (int y=0; y<800; y++) {
				int i = 4*(x + y*1024);
				Color8u color;
				dataArray[i] = color.r = 255;
				dataArray[i+1] = color.g = 255;
				dataArray[i+2] = color.b= 255;
			}
		}*/
		//gl::drawSolidCircle( Vec2f( Starbucks[i].x*800, (1-Starbucks[i].y)*600) , 1.0f);
	//}
}

CINDER_APP_BASIC( HW04Gaydads5App, RendererGl )

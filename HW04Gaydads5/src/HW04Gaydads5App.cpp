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
	return arr;
}

  

void HW04Gaydads5App::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(windowWidth,windowHeight);
	(*settings).setResizable(false);
}

void HW04Gaydads5App::setup() {
	myImage = gl::Texture( loadImage( loadResource( RES_IMAGE, "IMAGE" ) ) );
	structure = new gaydadsStarbucks();
	Entry* AllStarbucks = readFile();
	Entry* location;
	
	structure->build(AllStarbucks,7655);
	
	location = structure->getNearest(.5,.5);
	HW04Gaydads5App::console() <<location->identifier <<std::endl;
	Starbucks = AllStarbucks;
}

void HW04Gaydads5App::mouseDown( MouseEvent event )
{
}

void HW04Gaydads5App::update()
{
}

void HW04Gaydads5App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::draw( myImage, getWindowBounds() );
	gl::drawSolidCircle( Vec2f( 575.0f, 175.0f ), 5.0f  );
	for(int i = 0; i < 7655; i++){
		gl::drawSolidCircle( Vec2f((Starbucks[i].x *550)+25, (Starbucks[i].y*(-375))+490), 1.0f);
	}
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

}

CINDER_APP_BASIC( HW04Gaydads5App, RendererGl )

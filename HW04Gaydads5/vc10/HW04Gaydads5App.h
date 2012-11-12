#pragma once
#include "cinder/ImageIo.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Starbucks.h"
#include "gaydadsStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;
class CensusEntry;
class StarbucksColor;
class HW04Gaydads5App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	Entry* readFile();
	CensusEntry* readcensus2000();
	CensusEntry* readcensus2010();
	gaydadsStarbucks* structure;
	gl::Texture myImage;
	void prepareSettings(Settings* settings);
	StarbucksColor* getNearest(double x,double y);
	CensusEntry* arr2010;
	CensusEntry* arr2000;
	Surface* mySurface;
	uint8_t* pixels;
	Surface* zoomSurf;
	uint8_t* zoomPix;
	uint8_t* dataArray;
	int zoomConst;
	int yOffset;  // For zoom
	int xOffset;  // For zoom

private:
	Surface* mySurface_; //The Surface object whose pixel array we will modify
	gl::Texture* myTexture; //The Texture object that we use to display our Surface in the window

	static const int windowWidth=800;
	static const int windowHeight=600;
	static const int surfaceSize=1024;
	Entry* Starbucks;
	Vec2i mousePos;
	bool clicked;
	double mouse_x,mouse_y;
	int* state_pop_2000;
	int* state_pop_2010;
	

};

class CensusEntry {
public:

	int stateID;
	int population;
	double x;
	double y;
};

class StarbucksColor {
public:
	string identifier;
	double x;
	double y;
	Color8u color;
	StarbucksColor* Locations;
};
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

class HW04Gaydads5App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	Entry* readFile();
	gaydadsStarbucks* structure;
	gl::Texture myImage;
	void prepareSettings(Settings* settings);
private:
	Surface* mySurface;
	static const int windowWidth=600;
	static const int windowHeight=600;
	static const int surfaceSize=1024;
	Entry* Starbucks;

};
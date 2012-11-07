#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04Gaydads5App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04Gaydads5App::setup()
{
	//Comment!
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
}

CINDER_APP_BASIC( HW04Gaydads5App, RendererGl )

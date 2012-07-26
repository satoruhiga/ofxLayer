#include "testApp.h"

#include "ofxLayer.h"

class TestLayer1 : public ofxLayer
{
public:
	
	void update()
	{
		ofBackground(0, 0, 0, 0);
	}

	void draw()
	{
		ofSetColor(0, 255, 0);
		ofRect(ofGetMouseX()-50, ofGetMouseY()-50, 100, 100);
	}

};

class TestLayer2 : public ofxLayer
{
public:
	
	void update()
	{
		ofBackground(0, 0, 0, 0);
	}
	
	void draw()
	{
		ofSetColor(255, 0, 0);
		ofRect(ofGetMouseX(), ofGetMouseY(), 100, 100);
	}
};

TestLayer1 *layer1;
TestLayer2 *layer2;

ofxLayerManager &mng = ofxLayerManager::instance();

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofBackground(30);
	
	mng.setup(1280, 720);
	
	layer1 = mng.createLayer<TestLayer1>();
	layer2 = mng.createLayer<TestLayer2>();
}

//--------------------------------------------------------------
void testApp::update()
{
	mng.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofEnableAlphaBlending();
	
	mng.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	if (key == '1') layer1->moveUp();
	if (key == '2') layer1->moveDown();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
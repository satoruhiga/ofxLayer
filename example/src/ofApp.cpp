#include "ofMain.h"

#include "ofxLayer.h"

using namespace ofxLayer;

class TestLayer1 : public ofxLayer::Layer
{
public:
	
	OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer1);
	
	void update()
	{
		ofBackground(0, 0, 0, 0);
	}
	
	void draw()
	{
		ofSetColor(0, 255, 0);
		ofRect(ofGetMouseX(), ofGetMouseY(), 100, 100);
		ofDrawBitmapString(ofToString(__PRETTY_FUNCTION__), 10, 20 + 20 * getLayerIndex());
	}
};

class TestLayer2 : public ofxLayer::Layer
{
public:
	
	OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer2);
	
	void update()
	{
		ofBackground(0, 0, 0, 0);
	}
	
	void draw()
	{
		ofSetColor(255, 0, 0);
		ofRect(ofGetMouseX() + 10, ofGetMouseY() + 10, 100, 100);
		ofDrawBitmapString(ofToString(__PRETTY_FUNCTION__), 10, 20 + 20 * getLayerIndex());
	}
};

class TestLayer3 : public ofxLayer::Layer
{
public:
	
	OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer3);
	
	void update()
	{
		ofBackground(0, 0, 0, 0);
	}
	
	void draw()
	{
		ofSetColor(0, 0, 255);
		ofRect(ofGetMouseX() + 20, ofGetMouseY() + 20, 100, 100);
		ofDrawBitmapString(ofToString(__PRETTY_FUNCTION__), 10, 20 + 20 * getLayerIndex());
	}
};

TestLayer1 *layer1;
TestLayer2 *layer2;
TestLayer3 *layer3;

ofxLayer::Manager mng;

class ofApp : public ofBaseApp
{
public:
	void setup()
	{
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		ofBackground(0);
		
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		
		ofBackground(30);
		
		mng.setup(1280, 720);
		
		layer1 = mng.createLayer<TestLayer1>(1);
		layer2 = mng.createLayer<TestLayer2>(1);
		layer3 = mng.createLayer<TestLayer3>(1);
	}
	
	void update()
	{
		mng.update();
		ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
	}
	
	void draw()
	{
		ofEnableAlphaBlending();
		mng.draw();
	}

	void keyPressed(int key)
	{
		if (key == '1') layer3->moveUp();
		if (key == '2') layer3->moveDown();
	}

	void keyReleased(int key)
	{
	}
	
	void mouseMoved(int x, int y)
	{
	}

	void mouseDragged(int x, int y, int button)
	{
	}

	void mousePressed(int x, int y, int button)
	{
	}

	void mouseReleased(int x, int y, int button)
	{
	}
	
	void windowResized(int w, int h)
	{
	}
};


int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}

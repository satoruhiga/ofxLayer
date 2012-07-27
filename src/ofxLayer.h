#pragma once

#include "ofMain.h"
#include "ofxLayerManager.h"

class ofxLayer
{
public:
	
	friend class ofxLayerManager;
	
	virtual const char* getName() { throw runtime_error("ofxLayer::getName() must override"); return NULL; }
	
	virtual void setup() {}
	virtual void update() {}
	virtual void draw() {}
	
	void setEnable(bool v) { enable = v; }
	bool getEnable() { return enable; }
	
	void setVisible(bool v) { visible = v; }
	bool getVisible() { return visible; }
	
	void setAlpha(float a) { enable = visible = alpha > 0; alpha = a; }
	float getAlpha() { return alpha; }
	
	int getLayerIndex();
	void setLayerIndex(int index);
	
	void moveFront();
	void moveBack();
	
	void moveUp();
	void moveDown();
	
	void mute();
	void solo();
	
public:
	
	ofxLayer();
	virtual ~ofxLayer();
	
protected:
	
	void ofBackground(int r, int g, int b, int a = 255);
	void ofBackground(int b, int a = 255);
	
	inline int ofGetWidth()
	{
		return frameBuffer.getWidth();
	}
	
	inline int ofGetHeight()
	{
		return frameBuffer.getHeight();
	}
	
	void registerLayer();
	void unregisterLayer();
	
protected:
	
	bool visible, enable;
	int layer_index;
	
	ofColor background;
	ofFbo frameBuffer;
	
	float alpha;
	
	void allocateFramebuffer(int width, int height);
	
	void layerSetup();
	void layerUpdate();
	void layerDraw();

};

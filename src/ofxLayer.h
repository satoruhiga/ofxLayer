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
	
	inline void setEnable(bool v) { enable = v; }
	inline bool getEnable() { return enable; }
	inline bool isEnable() { return getEnable(); }
	
	inline void setVisible(bool v) { visible = v; }
	inline bool getVisible() { return visible; }
	
	inline void setAlpha(float a) { enable = visible = alpha > 0; alpha = a; }
	inline float getAlpha() { return alpha; }
	
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
	
	inline ofRectangle ofGetCurrentViewport()
	{
		return ofRectangle(0, 0, frameBuffer.getWidth(), frameBuffer.getHeight());
	}
	
	inline int ofGetWidth()
	{
		return frameBuffer.getWidth();
	}
	
	inline int ofGetHeight()
	{
		return frameBuffer.getHeight();
	}
	
protected:
	
	ofxLayerManager *manager;
	
	bool visible, enable;
	float alpha;
	
	int layer_index;
	
	ofColor background;
	ofFbo frameBuffer;
	
	void allocateFramebuffer(int width, int height);
	
	void layerSetup();
	void layerUpdate();
	void layerDraw();

};

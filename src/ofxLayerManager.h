#pragma once

#include "ofMain.h"

class ofxLayer;

class ofxLayerManager
{
public:
	
	friend class ofxLayer;
	
	static ofxLayerManager& instance();
	
	ofxLayerManager();
	
	void setup(int width = ::ofGetWidth(), int height = ::ofGetHeight());
	void update();
	void draw();
	
	template <typename T>
	T* createLayer()
	{
		T *layer = new T;
		layer->allocateFramebuffer(width, height);
		layers.push_back(layer);
		updateLayerIndex();
		
		layer->layerSetup();
		
		return layer;
	}
	
	void deleteLayer(ofxLayer *layer);
	
	void mute(int index);
	void mute(ofxLayer *layer);
	
	void solo(int index);
	void solo(ofxLayer *layer);
	
	void updateLayerIndex();
	
protected:
	
	vector<ofxLayer*> layers;
	
private:
	
	ofxLayerManager(const ofxLayerManager&);
	ofxLayerManager& operator=(const ofxLayerManager&);
	~ofxLayerManager();
	
	static ofxLayerManager* _instance;
	
	int width, height;
};


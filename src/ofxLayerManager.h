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
		
		string name = layer->getName();
		
		if (layer_map.find(name) != layer_map.end())
			throw runtime_error("ofxLayer::getName() must be unique");
			
		layer_map[name] = layer;
		
		updateLayerIndex();
		
		layer->layerSetup();
		
		return layer;
	}
	
	void deleteLayer(ofxLayer *layer);
	
	vector<string> getLayerNames();
	const vector<ofxLayer*>& getLayers();
	
	void mute(int index);
	void mute(ofxLayer *layer);
	void mute(const string& name);
	
	void solo(int index);
	void solo(ofxLayer *layer);
	void solo(const string& name);
	
	ofxLayer* getLayerByName(const string& name);
	int getLayerIndexByName(const string& name);
	
protected:
	
	vector<ofxLayer*> layers;
	map<string, ofxLayer*> layer_map;
	
	void updateLayerIndex();
	
private:
	
	ofxLayerManager(const ofxLayerManager&);
	ofxLayerManager& operator=(const ofxLayerManager&);
	~ofxLayerManager();
	
	static ofxLayerManager* _instance;
	
	int width, height;
};


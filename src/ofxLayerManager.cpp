#include "ofxLayerManager.h"

#include "ofxLayer.h"

ofxLayerManager* ofxLayerManager::_instance = NULL;

ofxLayerManager& ofxLayerManager::instance()
{
	if (_instance == NULL)
		_instance = new ofxLayerManager;
	
	return *_instance;
}

ofxLayerManager::ofxLayerManager()
{
}

void ofxLayerManager::setup(int width_, int height_)
{
	width = width_;
	height = height_;
}

void ofxLayerManager::update()
{
	for (int i = 0; i < layers.size(); i++)
		layers[i]->layerUpdate();
}

void ofxLayerManager::draw()
{
	for (int i = 0; i < layers.size(); i++)
		layers[i]->layerDraw();
}

void ofxLayerManager::deleteLayer(ofxLayer *layer)
{
	assert(layer);
	
	vector<ofxLayer*>::iterator it = find(layers.begin(), layers.end(), layer);
	if (it == layers.end())
		layers.erase(it);
	
	updateLayerIndex();
	
	delete layer;
}

void ofxLayerManager::mute(int index)
{
	mute(layers.at(index));
}

void ofxLayerManager::mute(ofxLayer *layer)
{
	for (int i = 0; i < layers.size(); i++)
		if (layers[i] == layer) layers[i]->enable = false;
}

void ofxLayerManager::solo(int index)
{
	solo(layers.at(index));
}

void ofxLayerManager::solo(ofxLayer *layer)
{
	for (int i = 0; i < layers.size(); i++)
		layers[i]->enable = (layers[i] == layer);
}

void ofxLayerManager::updateLayerIndex()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->layer_index = i;
	}
}
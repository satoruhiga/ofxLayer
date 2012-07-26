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
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	ofEnableAlphaBlending();
	glDisable(GL_DEPTH_TEST);
	
	for (int i = 0; i < layers.size(); i++)
		layers[i]->layerDraw();
	
	glPopAttrib();
}

void ofxLayerManager::deleteLayer(ofxLayer *layer)
{
	assert(layer);
	
	vector<ofxLayer*>::iterator it = find(layers.begin(), layers.end(), layer);
	if (it == layers.end())
	{
		layer_map.erase(layer->getName());
		layers.erase(it);
	}
	
	updateLayerIndex();
	
	delete layer;
}

vector<string> ofxLayerManager::getLayerNames()
{
	vector<string> names;
	for (int i = 0; i < layers.size(); i++)
		names.push_back(layers[i]->getName());
	return names;
}

const vector<ofxLayer*>& ofxLayerManager::getLayers()
{
	return layers;
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

void ofxLayerManager::mute(const string& name)
{
	mute(getLayerByName(name));
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

void ofxLayerManager::solo(const string& name)
{
	solo(getLayerByName(name));
}

void ofxLayerManager::updateLayerIndex()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->layer_index = i;
	}
}

ofxLayer* ofxLayerManager::getLayerByName(const string& name)
{
	return layer_map[name];
}

int ofxLayerManager::getLayerIndexByName(const string& name)
{
	return layer_map[name]->layer_index;
}

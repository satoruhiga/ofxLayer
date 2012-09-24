#include "ofxLayerManager.h"

#include "ofxLayer.h"

ofxLayerManager::ofxLayerManager() : background(0, 0), backgroundAuto(true)
{
}

void ofxLayerManager::setup(int width_, int height_)
{
	width = width_;
	height = height_;
	
	frameBuffer.allocate(width, height, GL_RGBA);
}

void ofxLayerManager::update()
{
	for (int i = 0; i < layers.size(); i++)
		layers[i]->layerUpdate();
}

void ofxLayerManager::draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_DEPTH_TEST);
		
		frameBuffer.begin();
		
		if (backgroundAuto)
			ofClear(background.r, background.g, background.b, background.a);
		
		vector<ofxLayer*>::reverse_iterator it = layers.rbegin();
		while (it != layers.rend())
		{
			(*it)->layerDraw();
			it++;
		}
		frameBuffer.end();
	}
	glPopAttrib();
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		ofEnableAlphaBlending();
		ofSetColor(255, 255);
		frameBuffer.draw(0, 0);
	}
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

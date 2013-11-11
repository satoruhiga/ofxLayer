#include "ofxLayerManager.h"

#include "ofxLayer.h"

OFX_LAYER_BEGIN_NAMESPACE

Manager::Manager() : background(0, 0), backgroundAuto(true)
{
}

void Manager::setup(int width_, int height_)
{
	width = width_;
	height = height_;
	
	frameBuffer.allocate(width, height, GL_RGBA);
	layerFrameBuffer.allocate(width, height, GL_RGBA);
}

void Manager::update()
{
	for (int i = 0; i < layers.size(); i++)
		layers[i]->layerUpdate();
}

void Manager::draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		ofDisableDepthTest();
		
		frameBuffer.begin();
		
		if (backgroundAuto)
			ofClear(background.r, background.g, background.b, background.a);
		
		vector<Layer*>::reverse_iterator it = layers.rbegin();
		while (it != layers.rend())
		{
			Layer *layer = *it;
			
			if (layer->visible)
			{
				// render to fbo
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				{
					layerFrameBuffer.begin(false);
					
					ofPushStyle();
					glPushMatrix();
					
					ofDisableAlphaBlending();
					ofDisableSmoothing();
					ofDisableDepthTest();
					
					ofClear(layer->background.r);
					
					layer->draw();
					
					glPopMatrix();
					ofPopStyle();
					
					frameBuffer.end();
				}
				glPopAttrib();
				
				// draw fbo
				ofSetColor(255, layer->alpha * 255);
				layerFrameBuffer.draw(0, layerFrameBuffer.getHeight(),
									  layerFrameBuffer.getWidth(), -layerFrameBuffer.getHeight());
			}
			
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

void Manager::deleteLayer(Layer *layer)
{
	assert(layer);
	
	vector<Layer*>::iterator it = find(layers.begin(), layers.end(), layer);
	if (it == layers.end())
	{
		layer_class_name_map.erase(layer->getClassName());
		layer_class_id_map.erase(layer->getClassID());
		layers.erase(it);
	}
	
	delete layer;
}

vector<string> Manager::getLayerNames()
{
	vector<string> names;
	for (int i = 0; i < layers.size(); i++)
		names.push_back(layers[i]->getClassName());
	return names;
}

const vector<Layer*>& Manager::getLayers()
{
	return layers;
}

void Manager::mute(int index)
{
	mute(layers.at(index));
}

void Manager::mute(Layer *layer)
{
	for (int i = 0; i < layers.size(); i++)
		if (layers[i] == layer) layers[i]->visible = false;
}

void Manager::mute(const string& name)
{
	mute(getLayerByName(name));
}

void Manager::solo(int index)
{
	solo(layers.at(index));
}

void Manager::solo(Layer *layer)
{
	for (int i = 0; i < layers.size(); i++)
		layers[i]->visible = (layers[i] == layer);
}

void Manager::solo(const string& name)
{
	solo(getLayerByName(name));
}

Layer* Manager::getLayerByName(const string& name)
{
	return layer_class_name_map[name];
}

int Manager::getLayerIndexByName(const string& name)
{
	return layer_class_name_map[name]->layer_index;
}

OFX_LAYER_END_NAMESPACE

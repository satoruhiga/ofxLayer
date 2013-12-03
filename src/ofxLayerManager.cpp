#include "ofxLayerManager.h"

#include "ofxLayer.h"

OFX_LAYER_BEGIN_NAMESPACE

Manager::Manager() : backgroundAuto(true)
{
}

void Manager::setup(int width_, int height_)
{
	width = width_;
	height = height_;
	
	ofFbo::Settings s;
	s.width = width;
	s.height = height;
	s.useDepth = true;
	s.useStencil = true;
	s.internalformat = GL_RGBA;
	
	frameBuffer.allocate(s);
	layerFrameBuffer.allocate(s);
}

void Manager::update()
{
	for (int i = 0; i < layers.size(); i++)
		layers[i]->layerUpdate();
}

void Manager::draw()
{
	ofPushStyle();
	{
		ofDisableDepthTest();
		
		frameBuffer.begin();
		
		if (backgroundAuto)
		{
			ofColor background = ofGetStyle().bgColor;
			ofClear(background.r, background.g, background.b, 0);
		}
		
		vector<Layer*>::reverse_iterator it = layers.rbegin();
		while (it != layers.rend())
		{
			Layer *layer = *it;
			
			if (layer->visible)
			{
				// render to fbo
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				{
					layerFrameBuffer.begin();
					
					ofPushStyle();
					glPushMatrix();
					
					ofDisableSmoothing();
					ofEnableDepthTest();
					ofEnableAlphaBlending();
					ofDisableLighting();
					
					ofClear(layer->background);
					ofSetColor(255, 255);
					
					layer->draw();
					
					glPopMatrix();
					ofPopStyle();
					
					layerFrameBuffer.end();
				}
				glPopAttrib();
				
				// draw fbo
				ofSetColor(255, layer->alpha * 255);
				layerFrameBuffer.draw(0, 0);
			}
			
			it++;
		}
		
		frameBuffer.end();
	}
	ofPopStyle();

	frameBuffer.draw(0, 0);
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

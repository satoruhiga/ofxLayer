#include "ofxLayerManager.h"

#include "ofxLayer.h"

OFX_LAYER_BEGIN_NAMESPACE

Manager::Manager()
	: backgroundAuto(true)
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
	s.internalformat = GL_RGB;

	layerFrameBuffer.allocate(s);
	
	s.internalformat = GL_RGB;
	frameBuffer.allocate(s);
}

void Manager::update()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->layerUpdate();
	}
	
	ofPushStyle();
	{
		ofDisableDepthTest();
		
		frameBuffer.begin();
		
		if (backgroundAuto)
		{
			ofColor background = ofGetStyle().bgColor;
			ofClear(background.r, background.g, background.b, 0);
		}
		
		frameBuffer.end();
		
		vector<Layer*>::reverse_iterator it = layers.rbegin();
		while (it != layers.rend())
		{
			Layer* layer = *it;
			
			if (layer->isVisible())
			{
				// render to layer fbo
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				{
					layerFrameBuffer.begin();
					
					ofPushStyle();
					glPushMatrix();
					
					ofDisableSmoothing();
					ofEnableDepthTest();
					ofDisableLighting();
					
					ofClear(layer->background);
					ofSetColor(255, 255);
					
					layer->draw();
					
					glPopMatrix();
					ofPopStyle();
					
					layerFrameBuffer.end();
				}
				glPopAttrib();
				
				frameBuffer.begin();
				
				// render to main fbo
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				{
					ofDisableDepthTest();
					ofSetColor(255, layer->alpha * 255);
					
					ofEnableBlendMode(layer->getBlendMode());
					layerFrameBuffer.draw(0, 0);
					ofDisableBlendMode();
				}
				glPopAttrib();
				
				frameBuffer.end();
			}
			
			it++;
		}
	}
	ofPopStyle();
}

void Manager::draw()
{
	frameBuffer.draw(0, 0);
}

void Manager::deleteLayer(Layer* layer)
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

const vector<Layer*>& Manager::getLayers() { return layers; }

Layer* Manager::getLayerByName(const string& name)
{
	return layer_class_name_map[name];
}

int Manager::getLayerIndexByName(const string& name)
{
	return layer_class_name_map[name]->layer_index;
}

void Manager::updateLayerIndex()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->layer_index = i;
	}
}

OFX_LAYER_END_NAMESPACE

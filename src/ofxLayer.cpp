#include "ofxLayer.h"

ofxLayer::ofxLayer() : visible(true), enable(true), alpha(1)
{
}

ofxLayer::~ofxLayer()
{
}

void ofxLayer::allocateFramebuffer(int width, int height)
{
	frameBuffer.allocate(width, height, GL_RGBA);
}

void ofxLayer::layerSetup()
{
	float *bg = ofBgColorPtr();
	background.set(bg[0] * 255, bg[1] * 255, bg[2] * 255);
	setup();
}

void ofxLayer::layerUpdate()
{
	if (!enable) return;
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		update();
		
		frameBuffer.begin();
		
		ofPushStyle();
		glPushMatrix();
		
		ofDisableAlphaBlending();
		ofDisableSmoothing();
		
		ofClear(background.r, background.g, background.b, background.a);
		
		draw();
		
		glPopMatrix();
		ofPopStyle();
		
		frameBuffer.end();
	}
	glPopAttrib();
}

void ofxLayer::layerDraw()
{
	if (!enable) return;
	
	if (visible && alpha > 0)
	{
		ofSetColor(255, alpha * 255);
		frameBuffer.draw(0, 0, frameBuffer.getWidth(), frameBuffer.getHeight());
	}
}

void ofxLayer::ofBackground(int r, int g, int b, int a)
{
	background.set(r, g, b, a);
}

void ofxLayer::ofBackground(int b, int a)
{
	background.set(b, a);
}

int ofxLayer::getLayerIndex()
{
	return layer_index;
}

void ofxLayer::setLayerIndex(int index)
{
	vector<ofxLayer*> &layers = ofxLayerManager::instance().layers;
	if (index < 0 || index >= layers.size()) return;
	
	vector<ofxLayer*>::iterator it = layers.begin();
	iter_swap(it + layer_index, it + index);
	
	ofxLayerManager::instance().updateLayerIndex();
}

void ofxLayer::moveFront()
{
	setLayerIndex(0);
}

void ofxLayer::moveBack()
{
	vector<ofxLayer*> &layers = ofxLayerManager::instance().layers;
	setLayerIndex(layers.size() - 1);
}

void ofxLayer::moveUp()
{
	setLayerIndex(layer_index - 1);
}

void ofxLayer::moveDown()
{
	setLayerIndex(layer_index + 1);
}

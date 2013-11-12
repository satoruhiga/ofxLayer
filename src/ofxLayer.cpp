#include "ofxLayer.h"

OFX_LAYER_BEGIN_NAMESPACE

Layer::Layer() : manager(NULL), visible(false), alpha(0)
{
}

Layer::~Layer()
{
}

void Layer::layerSetup(int width, int height)
{
	float *bg = ofBgColorPtr();
	background.set(bg[0] * 255, bg[1] * 255, bg[2] * 255, 0);
	rect.width = width;
	rect.height = height;
	setup();
}

void Layer::layerUpdate()
{
	if (!visible) return;
	
	update();
}

void Layer::ofBackground(int r, int g, int b, int a)
{
	background.set(r, g, b, a);
}

void Layer::ofBackground(int b, int a)
{
	background.set(b, a);
}

int Layer::getLayerIndex()
{
	return layer_index;
}

void Layer::setLayerIndex(int index)
{
	vector<Layer*> &layers = manager->layers;
	if (index < 0 || index >= layers.size()) return;
	
	vector<Layer*>::iterator it = layers.begin();
	iter_swap(it + layer_index, it + index);
}

void Layer::moveFront()
{
	setLayerIndex(0);
}

void Layer::moveBack()
{
	vector<Layer*> &layers = manager->layers;
	setLayerIndex(layers.size() - 1);
}

void Layer::moveUp()
{
	setLayerIndex(layer_index - 1);
}

void Layer::moveDown()
{
	setLayerIndex(layer_index + 1);
}

void Layer::mute()
{
	manager->mute(this);
}

void Layer::solo()
{
	manager->solo(this);
}

OFX_LAYER_END_NAMESPACE

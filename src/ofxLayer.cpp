#include "ofxLayer.h"

OFX_LAYER_BEGIN_NAMESPACE

Layer::Layer()
	: manager(NULL)
	, alpha(0)
	, blendMode(OF_BLENDMODE_ALPHA)
{
}

Layer::~Layer() {}

void Layer::layerSetup(int width, int height)
{
	background = ofGetBackgroundColor();
	rect.width = width;
	rect.height = height;
	setup();
}

void Layer::layerUpdate()
{
	updateEvery();

	if (!isVisible()) return;

	update();
}

void Layer::ofBackground(int r, int g, int b, int a)
{
	background.set(r, g, b, a);
}

void Layer::ofBackground(int b, int a) { background.set(b, a); }

int Layer::getLayerIndex() { return layer_index; }

void Layer::setLayerIndex(int index)
{
	vector<Layer*>& layers = manager->layers;

	if (index < 0 || index >= layers.size()) return;

	Layer* self = layers[layer_index];
	layers.erase(layers.begin() + layer_index);

	layers.insert(layers.begin() + index, self);
	manager->updateLayerIndex();
}

void Layer::moveFront() { setLayerIndex(0); }

void Layer::moveBack()
{
	vector<Layer*>& layers = manager->layers;
	setLayerIndex(layers.size() - 1);
}

void Layer::moveUp() { setLayerIndex(layer_index - 1); }

void Layer::moveDown() { setLayerIndex(layer_index + 1); }

OFX_LAYER_END_NAMESPACE

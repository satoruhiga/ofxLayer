#pragma once

#define OFX_LAYER_BEGIN_NAMESPACE namespace ofx { namespace Layer {
#define OFX_LAYER_END_NAMESPACE } }

OFX_LAYER_BEGIN_NAMESPACE

template<typename T>
struct Type2Int
{
	static unsigned int value()
	{
		static size_t m = 0;
		return (unsigned int)&m;
	}
};

OFX_LAYER_END_NAMESPACE

namespace ofxLayer = ofx::Layer;


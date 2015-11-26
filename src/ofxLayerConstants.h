#pragma once

#define OFX_LAYER_BEGIN_NAMESPACE namespace ofx { namespace Layer {
#define OFX_LAYER_END_NAMESPACE } }

OFX_LAYER_BEGIN_NAMESPACE

typedef void* TYPE_ID;

template<typename T>
struct RTTI
{
	static TYPE_ID value()
	{
		static size_t m = 0;
		return (TYPE_ID)&m;
	}
};

OFX_LAYER_END_NAMESPACE

namespace ofxLayer = ofx::Layer;


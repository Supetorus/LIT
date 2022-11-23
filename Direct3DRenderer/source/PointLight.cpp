#include "PointLight.h"
#include "renderer/ConstantBuffer.h"

namespace wl
{

	void PointLight::Bind()
	{
		ConstantBuffer light(sizeof(LightData), ShaderStage::Pixel);
		light.SetData(&data);
		light.Bind(0);
	}

}
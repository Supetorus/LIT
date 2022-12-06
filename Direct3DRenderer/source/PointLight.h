#pragma once
#include "renderer/DX.h"

namespace wl
{

	struct PointLight
	{
		dx::XMFLOAT4 ambient{ 0.2f, 0.2f, 0.2f, 0 };
		dx::XMFLOAT4 diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
		dx::XMFLOAT4 specular{ 1.0f, 1.0f, 1.0f, 1.0f };
		alignas(16) dx::XMFLOAT3 position{ 0, 0, 0 };
		dx::XMFLOAT3 attenuation{ 1.0f, 0.045f, 0.0075f };
		float range{ 50 };
	};

}
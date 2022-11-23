#pragma once
#include "renderer/DX.h"
#include "Transform.h"

namespace wl
{
	class Renderer;

	class PointLight
	{
	public:
		PointLight()=default;
		void Bind();
	private:
		struct LightData
		{
			alignas(16) dx::XMFLOAT3 position{0, 0, 0};
			alignas(16) float diffuseIntensity{ 1.0f };
			alignas(16) float attConst{ 1.0f };
			alignas(16) float attLin{ 0.045f };
			alignas(16) float attQuad{ 0.0075f };
		} data{};
	};

}
#pragma once
#include "renderer/DX.h"
#include "Transform.h"

namespace wl
{
	class Renderer;
	class Camera;

	class PointLight
	{
	public:
		PointLight()=default;
		/// <summary>
		/// Binds the light to the pixel shader.
		/// </summary>
		void Bind(const Camera& camera);
		Transform transform;
	private:
		struct LightData
		{
			alignas(16) dx::XMFLOAT3 position{};
			float diffuseIntensity{ 1.0f };
			float attConst{ 1.0f };
			float attLin{ 0.045f };
			float attQuad{ 0.0075f };
		} data{};
	};

}
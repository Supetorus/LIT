#include "PointLight.h"
#include "renderer/ConstantBuffer.h"
#include "Camera.h"

namespace wl
{

	void PointLight::Bind(const Camera& camera)
	{

		const Transform &cameraTransform = camera.transform;

		dx::XMMATRIX view
		{
			dx::XMMatrixRotationZ(cameraTransform.rotation.z) *
			dx::XMMatrixRotationX(cameraTransform.rotation.x) *
			dx::XMMatrixRotationY(cameraTransform.rotation.y) *
			dx::XMMatrixTranslation(cameraTransform.position.x, cameraTransform.position.y, cameraTransform.position.z)
		};

		data.position = { transform.position.x, transform.position.y, transform.position.z };

		const auto pos = dx::XMLoadFloat3(&data.position);
		dx::XMStoreFloat3(&data.position, dx::XMVector3Transform(pos, view));
		
		ConstantBuffer light(sizeof(LightData), ShaderStage::Pixel);
		light.SetData(&data);
		light.Bind(0);
	}

}
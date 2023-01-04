#include "App.h"
#include "Log.h"
#include "Renderer.h"
#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "Scene.h"
#include "SceneSerializer.h"
#include "Controller.h"
#include "DXContext.h"
#include <memory>
#include <filesystem>
#include <PointLight.h>

namespace lit
{
	App::App()
	{
		std::filesystem::current_path("assets/");
		m_gTimer.Reset();
		m_renderer = std::make_unique<Renderer>(m_window);
		m_scene = std::make_shared<Scene>();
	}

	void App::Run()
	{
		{
			SceneSerializer serializer;
			m_scene = serializer.Deserialize("scenes/rhino.scn");
		}
		m_renderer->SetCamera(m_scene->m_camera);

		Controller controller(m_scene, *m_renderer);

#pragma region lightStuff
		struct MaterialData
		{
			dx::XMFLOAT4 ambient{ 1.0f, 1.0f, 1.0f, 1.0f };
			dx::XMFLOAT4 diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
			dx::XMFLOAT4 specular{ 1.0f, 1.0f, 1.0f, 1.0f };
			dx::XMFLOAT4 reflect{};
		} material;

		struct CameraPosition
		{
			alignas(16) dx::XMFLOAT3 position;
		} camera;

		ConstantBuffer m(sizeof(MaterialData), ShaderStage::Pixel);
		ConstantBuffer c(sizeof(CameraPosition), ShaderStage::Pixel);

		m.SetData(&material);
		m.Bind(1);

		//std::vector<PointLight> lights;
		//lights.push_back(PointLight());
		//
		//int lightCount = lights.size();
		//int lightSize = sizeof(PointLight);

		//// Make buffer
		//wrl::ComPtr<ID3D11Buffer> buffer;
		//D3D11_BUFFER_DESC sbufferDesc = {  };
		//sbufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		//sbufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		//sbufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//sbufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		//sbufferDesc.ByteWidth = lightCount * lightSize;
		//sbufferDesc.StructureByteStride = lightSize;

		//D3D11_SUBRESOURCE_DATA sbufferData{};
		//sbufferData.pSysMem = lights.data();

		//ASSERT_HR(
		//	DXContext::Instance->m_device->CreateBuffer(&sbufferDesc, &sbufferData, &buffer),
		//	"Unable to create buffer."
		//);

		//// Make view
		//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		//srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		//srvDesc.Buffer.FirstElement = 0;
		//srvDesc.Buffer.NumElements = lightCount;

		//wrl::ComPtr<ID3D11ShaderResourceView> view;

		//ASSERT_HR(
		//	DXContext::Instance->m_device->CreateShaderResourceView(buffer.Get(), &srvDesc, &view),
		//	"Unable to get shader resource view."
		//);

		////view->

		//// Bind the lights
		//DXContext::Instance->m_context->PSSetShaderResources(1, 1, view.GetAddressOf());

		PointLightList lights;
		{
			PointLight light;
			light.diffuse = dx::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			light.specular = dx::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			light.position = dx::XMFLOAT3(-2, 0, 0);
			lights.Add(light);
		}
		{
			PointLight light;
			light.diffuse = dx::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
			light.specular = dx::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
			light.position = dx::XMFLOAT3(2, 0, 0);
			lights.Add(light);
		}
		lights.Bind(1);

#pragma endregion

		// Main loop
		while (!m_window.IsQuit())
		{
			m_window.DoMessagePump();
			Input::Instance.UpdateKeyStates();
			m_gTimer.Tick();

			//camera->Update(m_gTimer.GetDeltaTime());
			controller.Update(m_gTimer.GetDeltaTime());

#pragma region temp
		const Transform::f3 &t = m_scene->m_camera->transform.position;
			camera.position = dx::XMFLOAT3{ t.x, t.y, t.z };
			c.SetData(&camera);
			c.Bind(2);
#pragma endregion

			m_renderer->BeginFrame();

			m_scene->Draw(*m_renderer);

			m_renderer->EndFrame();
		}

		m_window.Close();
	}

}
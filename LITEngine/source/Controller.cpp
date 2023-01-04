#include "Controller.h"

#include "Camera.h"
#include "Scene.h"
#include "Input.h"
#include "resources/Model.h"
#include "Transform.h"
#include "core/util.h"
#include "renderer/Renderer.h"
#include "utilities/SceneSerializer.h"
#include <algorithm>
#include <string>
#include <iostream>

unsigned char lCtrlKey = 0x11;
unsigned char spaceKey = 0x20;
unsigned char tabKey = 0x09;
unsigned char plus = 0xbb;
unsigned char minus = 0xbd;

namespace lit
{

	Controller::Controller(std::shared_ptr<Scene> &scene, Renderer &renderer) :
		m_scene(scene),
		m_renderer(renderer)
	{ }

	void Controller::Update(float deltaTime)
	{
		if (Input::Instance.GetKeyPressed('F'))
		{ // swap modes
			m_isCameraMode = !m_isCameraMode;
			LOG(m_isCameraMode ? "Camera mode" : "Model mode, selected model: " + std::to_string(m_currentModel) + ' ' + m_scene->m_models[m_currentModel]->name);
		}

		if (Input::Instance.GetKeyDown(lCtrlKey))
		{ // Special keys
			if (Input::Instance.GetKeyPressed('S'))
			{ // ctrl + s saves scene
				LOG("Saving Scene.");
				SceneSerializer serializer;
				serializer.Serialize(m_scene->m_filepath, *m_scene);
			}
			else if (Input::Instance.GetKeyPressed('R'))
			{ // ctrl + r reloads scene from file
				LOG("Reloading Scene.");
				SceneSerializer serializer;
				m_scene = serializer.Deserialize(m_scene->m_filepath);
				m_renderer.SetCamera(m_scene->m_camera);
			}
			else if (Input::Instance.GetKeyPressed('D'))
			{ // ctrl + d duplicates model
				m_scene->AddModel(m_scene->m_models[m_currentModel]->Clone());
				LOG("Duplicating Model: {0}", m_scene->m_models[m_currentModel]->name);
			}
			else if (Input::Instance.GetKeyPressed('X'))
			{ // ctrl + x deletes model
				LOG("Deleting Model: {0}");
				m_scene->DeleteModel(m_currentModel);
				if (m_currentModel == m_scene->m_models.size()) m_currentModel = 0;
				LOG("Selected Model: " + std::to_string(m_currentModel) + ' ' + 
					((m_scene->m_models.size() > 0) ? m_scene->m_models[m_currentModel]->name : "")
				);
			}
			else if (Input::Instance.GetKeyPressed('W'))
			{
				if (m_isWireframe) m_renderer.SetModeFill();
				else m_renderer.SetModeWireframe();
				m_isWireframe = !m_isWireframe;
				LOG("Toggle wireframe mode");
			}
		}
		else if (m_isCameraMode)
		{ // Control Camera

			if (Input::Instance.GetKeyDown(plus))
			{
				auto precision = std::cout.precision(2);
				m_cameraSpeed = std::max(0.1f, m_cameraSpeed + 1.f * deltaTime);
				std::cout << "Camera Speed: " << m_cameraSpeed << '\r';
				std::cout.precision(precision);
			}
			if (Input::Instance.GetKeyDown(minus))
			{
				auto precision = std::cout.precision(2);
				m_cameraSpeed = std::max(0.1f, m_cameraSpeed - 1.f * deltaTime);
				std::cout << "Camera Speed: " << m_cameraSpeed << '\r';
				std::cout.precision(precision);
			}
			ManipulateTransform(m_scene->m_camera->transform, 1 * m_cameraSpeed, 0, 1, deltaTime);
		}
		else
		{ // Control Model
			if (Input::Instance.GetKeyDown(plus))
			{
				auto precision = std::cout.precision(2);
				m_controllerSpeed = std::max(0.1f, m_controllerSpeed + 1.f * deltaTime);
				std::cout << "Control Speed: " << m_controllerSpeed << '\r';
				std::cout.precision(precision);
			}
			if (Input::Instance.GetKeyDown(minus))
			{
				auto precision = std::cout.precision(2);
				m_controllerSpeed = std::max(0.1f, m_controllerSpeed - 1.f * deltaTime);
				std::cout << "Control Speed: " << m_controllerSpeed << '\r';
				std::cout.precision(precision);
			}
			if (Input::Instance.GetKeyPressed(tabKey))
			{
				m_currentModel = (m_currentModel + 1) % m_scene->m_models.size();
				LOG("Selected Model: " + std::to_string(m_currentModel) + ' ' + m_scene->m_models[m_currentModel]->name);
			}
			ManipulateTransform(m_scene->m_models[m_currentModel]->transform,
				1 * m_controllerSpeed, 0.5f * m_controllerSpeed, 1 * m_controllerSpeed, deltaTime);
		}
	}

}
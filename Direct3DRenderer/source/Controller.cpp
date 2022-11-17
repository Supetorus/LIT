#include "Controller.h"

#include "Camera.h"
#include "Scene.h"
#include "Input.h"
#include "resources/Model.h"
#include "Transform.h"
#include "core/util.h"
#include "utilities/SceneSerializer.h"
#include <string>

unsigned char lCtrlKey = 0x11;
unsigned char spaceKey = 0x20;
unsigned char tabKey = 0x09;

namespace wl
{

	Controller::Controller(Camera &camera, std::shared_ptr<Scene> &scene) :
		m_camera(camera),
		m_scene(scene)
	{

	}

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
				serializer.Serialize("scenes/test.scn", *m_scene);
			}
			else if (Input::Instance.GetKeyPressed('R'))
			{ // ctrl + r reloads scene from file
				LOG("Reloading Scene.");
				SceneSerializer serializer;
				m_scene = serializer.Deserialize("scenes/test.scn");
			}
		}
		else if (m_isCameraMode)
		{ // Control Camera
			ManipulateTransform(m_camera.transform, 1, 0, 1, deltaTime);
		}
		else
		{ // Control Model
			if (Input::Instance.GetKeyPressed(tabKey))
			{
				m_currentModel = (m_currentModel + 1) % m_scene->m_models.size();
				LOG("Selected Model: " + std::to_string(m_currentModel) + ' ' + m_scene->m_models[m_currentModel]->name);
			}
			ManipulateTransform(m_scene->m_models[m_currentModel]->transform, 1, 0.05f, 1, deltaTime);
		}
	}

}
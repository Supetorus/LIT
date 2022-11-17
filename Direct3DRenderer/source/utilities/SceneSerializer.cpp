#include "SceneSerializer.h"
#include "renderer/Shader.h"
#include "Scene.h"
#include "resources/Skybox.h"
#include "yaml-cpp/yaml.h"
#include "Camera.h"
#include <fstream>

namespace YAML
{
	template<>
	struct convert<wl::Transform>
	{
		static Node encode(const wl::Transform &transform)
		{
			Node node;
			node.push_back(transform.position);
			node.push_back(transform.rotation);
			node.push_back(transform.scale);
			return node;
		}

		static bool decode(const Node &node, wl::Transform &transform)
		{
			transform.position = node["Position"].as<wl::Transform::f3>();
			transform.rotation = node["Rotation"].as<wl::Transform::f3>();
			transform.scale = node["Scale"].as<wl::Transform::f3>();
			return true;
		}
	};

	template<>
	struct convert<wl::Transform::f3>
	{
		static Node encode(const wl::Transform::f3 &value)
		{
			Node node;
			node.push_back(value.x);
			node.push_back(value.y);
			node.push_back(value.z);
			return node;
		}

		static bool decode(const Node &node, wl::Transform::f3 &value)
		{
			value.x = node[0].as<float>();
			value.y = node[1].as<float>();
			value.z = node[2].as<float>();
			return true;
		}
	};
}

namespace wl
{
	YAML::Emitter &operator<< (YAML::Emitter &out, Transform transform)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Position";
		out << YAML::Value;
		out << YAML::Flow;
		out << YAML::BeginSeq;
		out << transform.position.x;
		out << transform.position.y;
		out << transform.position.z;
		out << YAML::EndSeq;

		out << YAML::Key << "Rotation";
		out << YAML::Value;
		out << YAML::Flow;
		out << YAML::BeginSeq;
		out << transform.rotation.x;
		out << transform.rotation.y;
		out << transform.rotation.z;
		out << YAML::EndSeq;

		out << YAML::Key << "Scale";
		out << YAML::Value;
		out << YAML::Flow;
		out << YAML::BeginSeq;
		out << transform.scale.x;
		out << transform.scale.y;
		out << transform.scale.z;
		out << YAML::EndSeq;

		out << YAML::EndMap;

		return out;
	}

	YAML::Emitter &operator<<(YAML::Emitter &out, const Model &model)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "Model" << YAML::Value << model.name;

		out << YAML::Key << "Transform";
		out << YAML::Value << model.transform;

		out << YAML::Key << "Mesh";
		out << YAML::Value << model.m_meshPath;

		out << YAML::Key << "Texture";
		out << YAML::Value << model.m_texturePath;

		out << YAML::EndMap;

		return out;
	}

	YAML::Emitter &operator<<(YAML::Emitter &out, const Camera &cam)
	{
		out << YAML::Key << "Camera";
		out << YAML::Value;
		out << YAML::BeginMap;
		out << YAML::Key << "Transform";
		out << YAML::Value << cam.transform;
		out << YAML::Key << "FOV";
		out << YAML::Value << cam.fov;
		out << YAML::Key << "NearPlane";
		out << YAML::Value << cam.nearPlane;
		out << YAML::Key << "FarPlane";
		out << YAML::Value << cam.farPlane;
		out << YAML::EndMap;
		return out;
	}

	void SceneSerializer::Serialize(const std::string &filepath, const Scene &scene) const
	{
		YAML::Emitter out;
		out << YAML::Comment("Scene");

		out << YAML::BeginMap;

		out << YAML::Key << "Path";
		out << YAML::Value << filepath;

		out << YAML::Key << "Models";
		out << YAML::Value;
		out << YAML::BeginSeq;
		for (auto& model : scene.m_models)
		{
			out << *model;
		}
		out << YAML::EndSeq;

		out << YAML::Key << "Skybox";
		out << YAML::Value << scene.m_skybox->GetCubeMap().GetTexturePath();

		out << *scene.m_camera;

		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	std::shared_ptr<Scene> SceneSerializer::Deserialize(const std::string &filepath) const
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());

		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		std::shared_ptr<Scene> scene = std::make_shared<Scene>();

		for (auto model : data["Models"])
		{
			std::string name = model["Model"].as<std::string>();
			Transform transform = model["Transform"].as<wl::Transform>();
			std::string meshPath = model["Mesh"].as<std::string>();
			std::string texturePath = model["Texture"].as<std::string>();
			std::shared_ptr<Model> m = std::make_shared<Model>(meshPath, texturePath, shader, name);
			m->transform = transform;
			scene->AddModel(m);
		}

		std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>(data["Skybox"].as<std::string>());
		scene->SetSkybox(skybox);

		scene->m_filepath = data["Path"].as<std::string>();

		if (auto cam = data["Camera"])
		{
			std::shared_ptr<Camera> camera = std::make_shared<Camera>();
			if (auto a = cam["Transform"])			camera->transform			= a.as<Transform>();
			if (auto a = cam["FOV"])				camera->fov					= a.as<float>();
			if (auto a = cam["NearPlane"])			camera->nearPlane			= a.as<float>();
			if (auto a = cam["FarPlane"])			camera->farPlane			= a.as<float>();
			scene->m_camera = camera;
		}
		else
		{
			scene->m_camera = std::make_shared<Camera>();
		}

		return scene;
	}

}
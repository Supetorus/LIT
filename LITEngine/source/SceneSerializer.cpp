#include "SceneSerializer.h"
#include "Shader.h"
#include "Scene.h"
#include "Skybox.h"
#include "yaml-cpp/yaml.h"
#include "Camera.h"
#include "Transform.h"
#include <fstream>
#include <unordered_map>

namespace YAML
{
	template<>
	struct convert<lit::Transform>
	{
		static Node encode(const lit::Transform &transform)
		{
			Node node;
			node.push_back(transform.position);
			node.push_back(transform.rotation);
			node.push_back(transform.scale);
			return node;
		}

		static bool decode(const Node &node, lit::Transform &transform)
		{
			if (auto a = node["Position"])	transform.position = a.as<lit::Transform::f3>();
			else transform.position = { 0, 0, 0 };
			if (auto a = node["Rotation"])	transform.rotation = a.as<lit::Transform::f3>();
			else transform.rotation = { 0, 0, 0 };
			if (auto a = node["Scale"])		transform.scale = a.as<lit::Transform::f3>();
			else transform.scale = { 1, 1, 1 };
			return true;
		}
	};

	template<>
	struct convert<lit::Transform::f3>
	{
		static Node encode(const lit::Transform::f3 &value)
		{
			Node node;
			node.push_back(value.x);
			node.push_back(value.y);
			node.push_back(value.z);
			return node;
		}

		static bool decode(const Node &node, lit::Transform::f3 &value)
		{
			value.x = node[0].as<float>();
			value.y = node[1].as<float>();
			value.z = node[2].as<float>();
			return true;
		}
	};
}

namespace lit
{
	YAML::Emitter &operator<< (YAML::Emitter &out, Transform transform)
	{
		out << YAML::BeginMap;

		if (transform.position != Transform::identity.position)
		{
			out << YAML::Key << "Position";
			out << YAML::Value;
			out << YAML::Flow;
			out << YAML::BeginSeq;
			out << transform.position.x;
			out << transform.position.y;
			out << transform.position.z;
			out << YAML::EndSeq;
		}

		if (transform.rotation != Transform::identity.rotation)
		{
			out << YAML::Key << "Rotation";
			out << YAML::Value;
			out << YAML::Flow;
			out << YAML::BeginSeq;
			out << transform.rotation.x;
			out << transform.rotation.y;
			out << transform.rotation.z;
			out << YAML::EndSeq;
		}

		if (transform.scale != Transform::identity.scale)
		{
			out << YAML::Key << "Scale";
			out << YAML::Value;
			out << YAML::Flow;
			out << YAML::BeginSeq;
			out << transform.scale.x;
			out << transform.scale.y;
			out << transform.scale.z;
			out << YAML::EndSeq;
		}

		out << YAML::EndMap;

		return out;
	}

	YAML::Emitter &operator<<(YAML::Emitter &out, const Model &model)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "Model" << YAML::Value << model.name;

		if (model.transform != Transform::identity)
		{
			out << YAML::Key << "Transform";
			out << YAML::Value << model.transform;
		}

		out << YAML::Key << "Mesh";
		out << YAML::Value << model.m_meshPath;

		out << YAML::Key << "Texture";
		out << YAML::Value << model.m_texturePath;

		out << YAML::Key << "Shader";
		out << YAML::Value << model.m_shader->m_name;

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
		out << YAML::Key << "Near Plane";
		out << YAML::Value << cam.nearPlane;
		out << YAML::Key << "Far Plane";
		out << YAML::Value << cam.farPlane;

		out << YAML::Key << "Clear Color";
		out << YAML::Value << YAML::Flow << YAML::BeginSeq;
		for (int i = 0; i < 4; i++)
		{
			out << cam.clearColor[i];
		}
		out << YAML::EndSeq;

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
		for (auto &model : scene.m_models)
		{
			out << *model;
		}
		out << YAML::EndSeq;

		if (scene.m_skybox)
		{
			out << YAML::Key << "Skybox";
			out << YAML::Value << scene.m_skybox->GetCubeMap().GetTexturePath();
		}

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

		std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
		shaders["Default"] = std::make_shared<Shader>();
		shaders["Phong"] = std::make_shared<Shader>(L"shaders/Phong_Pixel.cso", L"shaders/Phong_Vertex.cso", "Phong");

		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		for (auto model : data["Models"])
		{
			std::string name		= model["Model"].as<std::string>();
			std::string meshPath	= model["Mesh"].as<std::string>();
			std::string texturePath;
			if (auto t = model["Texture"]) texturePath = t.as<std::string>();
			else texturePath = "textures/white.png";
			std::shared_ptr<Shader> shader;
			if (auto s = model["Shader"]) shader = shaders[s.as<std::string>()];
			else shader = shaders["Default"];
			std::shared_ptr<Model> m = std::make_shared<Model>(meshPath, texturePath, shader, name);
			if (auto t = model["Transform"]) m->transform = t.as<lit::Transform>();
			else m->transform = Transform();
			scene->AddModel(m);
		}

		if (auto s = data["Skybox"])
		{
			std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>(s.as<std::string>());
			scene->SetSkybox(skybox);
		}

		scene->m_filepath = filepath;

		if (auto cam = data["Camera"])
		{
			std::shared_ptr<Camera> camera = std::make_shared<Camera>();
			if (auto a = cam["Transform"])			camera->transform = a.as<Transform>();
			if (auto a = cam["FOV"])				camera->fov = a.as<float>();
			if (auto a = cam["Near Plane"])			camera->nearPlane = a.as<float>();
			if (auto a = cam["Far Plane"])			camera->farPlane = a.as<float>();
			if (auto a = cam["Clear Color"]) for (int i = 0; i < 4; i++) camera->clearColor[i] = a[i].as<float>();
			scene->m_camera = camera;
		}
		else
		{
			scene->m_camera = std::make_shared<Camera>();
		}

		LOG("Scene Loaded {0}", scene->m_filepath);
		return scene;
	}

}
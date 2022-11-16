#pragma once
#include "Mesh.h"
#include "renderer/Shader.h"
#include "renderer/ConstantBuffer.h"
#include "Transform.h"
#include "Texture.h"
#include "Sampler.h"
#include <string>
#include <vector>

namespace YAML
{
	class Emitter;
}

namespace wl
{
	class Renderer;

	class Model
	{
		friend class SceneSerializer;
		friend YAML::Emitter &operator<< (YAML::Emitter &out, const Model &model);
	public:
		Model(const std::string &meshPath, const std::string &texturePath, std::shared_ptr<Shader> shader, std::string name = "unnamed model");
		void Draw(const Renderer &renderer) const;
		const std::shared_ptr<Shader> GetShader() const;
		std::string name{};
		Transform transform{};
	private:

		std::string m_meshPath{};
		std::string m_texturePath{};
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Texture> m_texture{};
		Sampler m_sampler{};
		std::shared_ptr<Mesh> m_mesh{};
	};

}

#pragma once
#include "resources/CubeMap.h"
#include "renderer/Shader.h"
#include "resources/Sampler.h"

namespace lit
{
	class Renderer;
	class CubeMap;
	class Mesh;

	class Skybox
	{
	public:
		Skybox(const std::string &texturePath);
		void Draw(const Renderer &renderer);
		const CubeMap &GetCubeMap() const;
	private:
		std::shared_ptr<CubeMap> m_cubemap;
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Mesh> m_cubeMesh;
		Sampler m_sampler;
	};

}

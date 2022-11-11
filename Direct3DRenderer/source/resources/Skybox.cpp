#include "Skybox.h"
#include "resources/Mesh.h"
#include "resources/CubeMap.h"

namespace wl
{

	Skybox::Skybox(const std::string &texturePath)
	{
		m_shader = std::make_shared<Shader>(L"shaders/Skybox_Pixel.cso", L"shaders/Skybox_Vertex.cso");
		m_cubeMesh = std::make_shared<Mesh>();
		texturePath;
	}

	void Skybox::Draw(const Renderer &renderer)
	{
		renderer;
	}
}
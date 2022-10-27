#pragma once
#include "Mesh.h"
#include "renderer/Shader.h"
#include "renderer/ConstantBuffer.h"

namespace wl
{
	class Renderer;

	class Model
	{
	public:
		Model(Mesh mesh, Shader shader, ConstantBuffer colorbuffer);
		void Draw(Renderer renderer);
	private:
		//std::shared_ptr<Mesh> m_mesh;
		//std::shared_ptr<Shader> m_shader;
		//std::shared_ptr<ConstantBuffer> m_cBuffer;
		std::optional<Mesh> m_mesh;
		std::optional<Shader> m_shader;
		std::optional<ConstantBuffer> m_cBuffer;
	};

}

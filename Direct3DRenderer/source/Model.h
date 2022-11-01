#pragma once
#include "Mesh.h"
#include "renderer/Shader.h"
#include "renderer/ConstantBuffer.h"
#include "Transform.h"

namespace wl
{
	class Renderer;

	class Model
	{
	public:
		Model(Mesh mesh, std::shared_ptr<Shader> shader, ConstantBuffer colorbuffer);
		void Bind();
		const std::shared_ptr<Shader> GetShader() const;
		const Mesh GetMesh() const;
		const ConstantBuffer GetColorBuffer() const;
	private:
		std::shared_ptr<Shader> m_shader; // pointer because it is shared.
		Mesh m_mesh;
		ConstantBuffer m_buffer;
	};

}

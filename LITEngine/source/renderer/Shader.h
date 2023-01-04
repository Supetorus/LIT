#pragma once
#include "core/core.h"
#include "d3d11.h"
#include <filesystem>
#include "renderer/DX.h"
#include "DirectXMath.h"

namespace YAML
{
	class Emitter;
}

namespace lit
{

	class Model;

	/// <summary>
	/// A rendering pipeline stage
	/// </summary>
	enum class ShaderStage
	{
		Vertex,
		Pixel
	};

	class Shader
	{
		friend YAML::Emitter &operator<< (YAML::Emitter &out, const Model &model);
	public:
		/// <summary>
		/// Uses the default shaders with no lighting or effects.
		/// </summary>
		Shader();
		/// <summary>
		/// Creates a shader with the given pixel shader and vertex shader.
		/// </summary>
		/// <param name="pPath">The path to the pixel shader</param>
		/// <param name="vPath">The path to the vertex shader</param>
		/// <param name="name">The name of this shader, used for serialization and deserialization.</param>
		Shader(const wchar_t *pPath, const wchar_t *vPath, const std::string &name);
		/// <summary>
		/// Binds the selected vertex and pixel shaders to the pipeline.
		/// </summary>
		void Bind();
	private:
		std::string m_name;
		/// <summary>
		/// Generates the correct input layout for the shaders from reflection.
		/// </summary>
		void generateInputLayout();
		void loadShader(const wchar_t *path, ShaderStage stage);
		wrl::ComPtr<ID3D11PixelShader> m_pixelShader;
		wrl::ComPtr<ID3D11VertexShader> m_vertexShader;
		wrl::ComPtr<ID3D11InputLayout> m_inputLayout;
		const wchar_t *m_vPath;
	};
}
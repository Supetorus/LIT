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

namespace wl
{
	class Model;
	enum class ShaderStage
	{
		Vertex,
		Pixel
	};

	class Shader
	{
		//friend class SceneSerializer;
		friend YAML::Emitter &operator<< (YAML::Emitter &out, const Model &model);
	public:
		Shader();
		Shader(const wchar_t *pPath, const wchar_t *vPath, const std::string &name);
		void Init(const wchar_t *pPath, const wchar_t *vPath, const std::string &name);
		void Bind();
	private:
		std::string m_name;
		void generateInputLayout();
		void loadShader(const wchar_t *path, ShaderStage stage);
		wrl::ComPtr<ID3D11PixelShader> m_pixelShader;
		wrl::ComPtr<ID3D11VertexShader> m_vertexShader;
		wrl::ComPtr<ID3D11InputLayout> m_inputLayout;
		const wchar_t *m_vPath;
	};
}
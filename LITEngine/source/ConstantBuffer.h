#pragma once
#include "core.h"
#include "Shader.h"
#include "d3d11.h"
namespace lit
{
	/// <summary>
	/// A constant buffer to be used in the rendering pipeline.
	/// </summary>
	class ConstantBuffer
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="size">The number of bytes this buffer will hold. Use sizeof(type) if your data is all in a struct.</param>
		/// <param name="shaderStage">What stage of the pipeline this buffer should be bound to.</param>
		ConstantBuffer(uint32_t size, ShaderStage shaderStage);
		/// <summary>
		/// Sets the data. To bind the buffer to the rendering stage call Bind.
		/// </summary>
		/// <param name="data">Pointer to the data to be bound.</param>
		void SetData(const void *data);
		/// <summary>
		/// Binds the data to the pipeline stage defined by stage at the given cbuffer slot.
		/// </summary>
		/// <param name="slot">The cbuffer slot this data should be bound to</param>
		void Bind(uint32_t slot = 0);
	private:
		wrl::ComPtr<ID3D11Buffer> m_buffer;
		ShaderStage m_stage;
		uint32_t m_size;
	};
}


#pragma once
#include "core/core.h"
#include "renderer/DX.h"
#include "PointLight.h"
#include <vector>

namespace wl
{
	//struct PointLight;

	class PointLightList
	{
	public:
		PointLightList();
		void Add(PointLight& light);
		void Remove(int index);
		PointLight *Get(int index);
		void Bind(int slot);
		size_t Size() const;
	private:
		void SetData();
		void MakeBuffer();
		void MakeView();
		std::vector<PointLight> m_list;
		wrl::ComPtr<ID3D11Buffer> m_buffer;
		wrl::ComPtr<ID3D11ShaderResourceView> m_view;
		int m_prevElementCount{ 0 };
		const int m_preAllocationSize{ 5 };
		int m_currentAllocationSize{ 0 };
	};

}

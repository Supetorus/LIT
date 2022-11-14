#pragma once
#include "resources/Model.h"
#include <vector>
#include <memory>

namespace wl
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;
		void Draw(const Renderer &renderer) const;
		void AddModel(std::shared_ptr<Model> model);
	private:
		std::vector<std::shared_ptr<Model>> m_models;
	};

}

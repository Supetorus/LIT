#pragma once
#include <string>

namespace wl
{
	class Scene;

	class SceneSerializer
	{
	public:
		void Serialize(const std::string &filepath, const Scene &scene);
	};

}

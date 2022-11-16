#pragma once
#include <string>
#include <memory>

namespace wl
{
	class Scene;
	class Model;

	class SceneSerializer
	{
	public:
		void Serialize(const std::string &filepath, const Scene &scene) const;
		std::shared_ptr<Scene> Deserialize(const std::string &filepath) const;
	private:
	};

}

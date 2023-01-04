#pragma once
#include <memory>
#include <vector>
#include <string>

namespace lit
{
	class Mesh;

	class MeshLoader
	{
	public:
		static std::shared_ptr<Mesh> LoadMesh(std::string filepath);
	};

}

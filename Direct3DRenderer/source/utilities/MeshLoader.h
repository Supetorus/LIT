#pragma once
#include <vector>
#include <string>

namespace wl
{
	class Mesh;

	class MeshLoader
	{
	public:
		static std::vector<Mesh *>* LoadMeshes(std::string filepath);
	};

}

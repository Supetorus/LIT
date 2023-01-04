#include "MeshLoader.h"
#include "core.h"
#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

namespace lit
{
	dx::XMFLOAT2 GetUVCoords(aiMesh *mesh, uint32_t index)
	{
		if (mesh->mTextureCoords[0] == nullptr)
			return { 0.0f, 0.0f };
		const auto coords = mesh->mTextureCoords[0][index];
		return { coords.x, coords.y };
	}

	std::shared_ptr<Mesh> MeshLoader::LoadMesh(std::string filepath)
	{
		Assimp::Importer importer;
		auto scene = importer.ReadFile(filepath,
			aiProcess_Triangulate
			| aiProcess_JoinIdenticalVertices
			| aiProcess_GenNormals
			| aiProcess_FlipWindingOrder	//assimp uses counter clockwise winding order by default.
			| aiProcess_MakeLeftHanded		// assimp uses right handed coordinates by default.
			| aiProcess_FlipUVs				// assimp default is bottom left origin.
		);

		ASSERT(
			scene != nullptr,
			"Object failed to import.",
			importer.GetErrorString()
		);

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		for (unsigned int k = 0; k < scene->mNumMeshes; k++)
		{
			auto assimpMesh = scene->mMeshes[k];

			std::vector<Mesh::Vertex> vertices;
			vertices.reserve(assimpMesh->mNumVertices);
			for (unsigned int i = 0; i < assimpMesh->mNumVertices; i++)
			{
				Mesh::Vertex vertex =
				{
					{
						assimpMesh->mVertices[i].x,
						assimpMesh->mVertices[i].y,
						assimpMesh->mVertices[i].z,
					},
					GetUVCoords(assimpMesh, i)
				};
				if (assimpMesh->HasNormals())
				{
					vertex.Normal =
					{
						assimpMesh->mNormals[i].x,
						assimpMesh->mNormals[i].y,
						assimpMesh->mNormals[i].z,
					};
				}
				vertices.push_back(vertex);
			}

			std::vector<uint16_t> indices;
			indices.reserve(assimpMesh->mNumFaces * 3);
			for (unsigned int i = 0; i < assimpMesh->mNumFaces; i++)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					indices.push_back(assimpMesh->mFaces[i].mIndices[j]);
				}
			}

			Mesh::SubMesh *submesh = new Mesh::SubMesh;
			submesh->name = assimpMesh->mName.C_Str();
			submesh->SetVertices(vertices.data(), sizeof(Mesh::Vertex), static_cast<uint32_t>(vertices.size()));
			submesh->SetIndices(indices.data(), static_cast<uint32_t>(indices.size()));

			mesh->AddSubMesh(submesh);
		}
		return mesh;
	}
}

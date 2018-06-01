#pragma once
#include <Base\NE_Common.h>
#include <Engine\Assets\Mesh.h>
#include <Assimp\include\assimp\Importer.hpp>
#include <Assimp\include\assimp\scene.h>
#include <Assimp\include\assimp\postprocess.h>
#include <Engine\Managers\AssetManager.h>
namespace NuclearEngine {
	namespace Internal {
	
		class AssimpImporter {
		public:
			Assets::Mesh & Load(const std::string& Path, const Managers::MeshLoadingDesc& desc);
		private:

			void ProcessNode(aiNode *node, const aiScene *scene);
			Assets::Mesh::SubMesh::SubMeshData ProcessMesh(aiMesh *mesh, const aiScene *scene);
			std::vector<Assets::Texture> ProcessMaterialTexture(aiMaterial *mat, aiTextureType type);
			
			Assets::Mesh model;
			std::vector<Assets::Mesh::SubMesh::SubMeshData> meshes_loaded;
			std::string directory;

			Managers::MeshLoadingDesc LoadingDesc;
		};
	}
}
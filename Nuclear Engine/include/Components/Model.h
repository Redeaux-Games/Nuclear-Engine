#pragma once
#include <Components\Mesh.h>
#include <string>
#include <vector>
#include <Shading\Material.h>

namespace NuclearEngine {
	namespace Components {

		class NEAPI Model
		{
		public:			
			Model();
			~Model();
			static void CreateCube(Model* model, std::vector<MeshTexture> Textures, float width = 1.0f, float  height = 1.0f, float  depth = 1.0f);
			virtual void Draw(API::Shader* shader);

			std::vector<Mesh> Meshes;
		};

	}
}
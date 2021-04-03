#pragma once

#include <3DEngine/Shader.h>
#include <3DEngine/mesh/Mesh.h>
#include <3DEngine/Renderer/RenderPass/RenderPassType.h>
#include <Utilities/Loaders/TextureLoader.h>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace RenderEngine {

	class Model {
	public:
		Model(const char *path);
		Model(const Mesh &mesh);
		Model(const std::vector<Mesh> &meshes);
		
		void Draw(Shader *shader, RenderPassType pass) const;

		inline std::vector<Mesh>& getMeshes() { return mMeshes; }
	private:
		std::vector<Mesh> mMeshes;
		std::string mDirectory;

		void loadModel(const std::string &path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		Texture* loadMaterialTexture(aiMaterial *mat, aiTextureType type, bool isSRGB);
	};

}

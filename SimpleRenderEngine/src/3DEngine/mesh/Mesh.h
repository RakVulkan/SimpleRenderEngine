#pragma once

#include "Material.h"

namespace RenderEngine {

	class Model;

	class Mesh 
	{
		friend Model;
	public:
		Mesh();
		Mesh(std::vector<glm::vec3> &positions, std::vector<unsigned int> &indices);
		Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec2> &uvs, std::vector<unsigned int> &indices);
		Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indices);
		Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &bitangents, std::vector<unsigned int> &indices);
		~Mesh();
		// Commits all of the buffers their attributes to the GPU driver
		void LoadData(bool interleaved = true);

		void Draw() const;

		inline void setPositions(std::vector<glm::vec3> &positions) { mPositions = positions; }
		inline void setUVs(std::vector<glm::vec2> &uvs) { mUVs = uvs; }
		inline void setNormals(std::vector<glm::vec3> &normals) { mNormals = normals; }
		inline void setTangents(std::vector<glm::vec3> &tangents) { mTangents = tangents; }
		inline void setBitangents(std::vector<glm::vec3> &bitangents) { mBitangents = bitangents; }
		inline void setIndices(std::vector<unsigned int> &indices) { mIndices = indices; }

		inline Material& getMaterial() { return mMaterial; }
	protected:
		unsigned int mVAO, mVBO, mIBO;
		Material mMaterial;

		std::vector<glm::vec3> mPositions;
		std::vector<glm::vec2> mUVs;
		std::vector<glm::vec3> mNormals;
		std::vector<glm::vec3> mTangents;
		std::vector<glm::vec3> mBitangents;

		std::vector<unsigned int> mIndices;
	};

}

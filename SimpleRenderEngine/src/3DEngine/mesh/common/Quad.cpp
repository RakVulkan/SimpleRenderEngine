#include "pch.h"
#include "Quad.h"

namespace RenderEngine {

	Quad::Quad() {
		mPositions.push_back(glm::vec3(-1, 1, 0));  mUVs.push_back(glm::vec2(0, 1)); mNormals.push_back(glm::vec3(0, 0, 1)); mTangents.push_back(glm::vec3(1, 0, 0)); mBitangents.push_back(glm::vec3(0, 1, 0));
		mPositions.push_back(glm::vec3(1, 1, 0));   mUVs.push_back(glm::vec2(1, 1)); mNormals.push_back(glm::vec3(0, 0, 1)); mTangents.push_back(glm::vec3(1, 0, 0)); mBitangents.push_back(glm::vec3(0, 1, 0));
		mPositions.push_back(glm::vec3(-1, -1, 0)); mUVs.push_back(glm::vec2(0, 0)); mNormals.push_back(glm::vec3(0, 0, 1)); mTangents.push_back(glm::vec3(1, 0, 0)); mBitangents.push_back(glm::vec3(0, 1, 0));
		mPositions.push_back(glm::vec3(1, -1, 0));  mUVs.push_back(glm::vec2(1, 0)); mNormals.push_back(glm::vec3(0, 0, 1)); mTangents.push_back(glm::vec3(1, 0, 0)); mBitangents.push_back(glm::vec3(0, 1, 0));

		mIndices.push_back(1); mIndices.push_back(0); mIndices.push_back(2);
		mIndices.push_back(3); mIndices.push_back(1); mIndices.push_back(2);

		LoadData();
	}

}

#include "pch.h"
#include "Mesh.h"

namespace RenderEngine {

	Mesh::Mesh() 
		: mVAO(0)
		, mVBO(0)
		, mIBO(0) 
	{
	}

	Mesh::Mesh(std::vector<glm::vec3> &positions, std::vector<unsigned int> &indices)
		: mPositions(positions)
		, mIndices(indices)
		, mVAO(0)
		, mVBO(0)
		, mIBO(0) 
	{
	}

	Mesh::Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec2> &uvs, std::vector<unsigned int> &indices)
		: mPositions(positions)
		, mUVs(uvs)
		, mIndices(indices)
		, mVAO(0)
		, mVBO(0)
		, mIBO(0) 
	{
	}

	Mesh::Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indices)
		: mPositions(positions)
		, mUVs(uvs)
		, mNormals(normals)
		, mIndices(indices)
		, mVAO(0)
		, mVBO(0)
		, mIBO(0) 
	{
	}

	Mesh::Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &bitangents, std::vector<unsigned int> &indices)
		: mPositions(positions)
		, mUVs(uvs)
		, mNormals(normals)
		, mTangents(tangents)
		, mBitangents(bitangents)
		, mIndices(indices)
		, mVAO(0)
		, mVBO(0)
		, mIBO(0) 
	{
	}

	Mesh::~Mesh()
	{	
	} 

	void Mesh::Draw() const 
	{
		glBindVertexArray(mVAO);
		if (mIndices.size() > 0) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
			glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, mPositions.size());
		}
		glBindVertexArray(0);
	}

	void Mesh::LoadData(bool interleaved) 
	{
		// Preprocess the mesh data in the format that was specified
		std::vector<float> data;
		if (interleaved) {
			for (unsigned int i = 0; i < mPositions.size(); i++) {
				data.push_back(mPositions[i].x);
				data.push_back(mPositions[i].y);
				data.push_back(mPositions[i].z);
				if (mNormals.size() > 0) {
					data.push_back(mNormals[i].x);
					data.push_back(mNormals[i].y);
					data.push_back(mNormals[i].z);
				}
				if (mUVs.size() > 0) {
					data.push_back(mUVs[i].x);
					data.push_back(mUVs[i].y);
				}
				if (mTangents.size() > 0) {
					data.push_back(mTangents[i].x);
					data.push_back(mTangents[i].y);
					data.push_back(mTangents[i].z);
				}
				if (mBitangents.size() > 0) {
					data.push_back(mBitangents[i].x);
					data.push_back(mBitangents[i].y);
					data.push_back(mBitangents[i].z);
				}
			}
		}
		else {
			for (unsigned int i = 0; i < mPositions.size(); i++) {
				data.push_back(mPositions[i].x);
				data.push_back(mPositions[i].y);
				data.push_back(mPositions[i].z);
			}
			for (unsigned int i = 0; i < mNormals.size(); i++) {
				data.push_back(mNormals[i].x);
				data.push_back(mNormals[i].y);
				data.push_back(mNormals[i].z);
			}
			for (unsigned int i = 0; i < mUVs.size(); i++) {
				data.push_back(mUVs[i].x);
				data.push_back(mUVs[i].y);
			}
			for (unsigned int i = 0; i < mTangents.size(); i++) {
				data.push_back(mTangents[i].x);
				data.push_back(mTangents[i].y);
				data.push_back(mTangents[i].z);
			}
			for (unsigned int i = 0; i < mBitangents.size(); i++) {
				data.push_back(mBitangents[i].x);
				data.push_back(mBitangents[i].y);
				data.push_back(mBitangents[i].z);
			}
		}

		// Compute the component count
		unsigned int bufferComponentCount = 0;
		if (mPositions.size() > 0)
			bufferComponentCount += 3;
		if (mNormals.size() > 0)
			bufferComponentCount += 3;
		if (mUVs.size() > 0)
			bufferComponentCount += 2;
		if (mTangents.size() > 0)
			bufferComponentCount += 3;
		if (mBitangents.size() > 0)
			bufferComponentCount += 3;

		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mIBO);

		// Load data into the index buffer and vertex buffer
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
		if (mIndices.size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);
		}

		// Setup the format for the VAO
		if (interleaved) {
			size_t stride = bufferComponentCount * sizeof(float);
			size_t offset = 0;

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
			offset += 3 * sizeof(float);
			if (mNormals.size() > 0) {
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
				offset += 3 * sizeof(float);
			}
			if (mUVs.size() > 0) {
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)offset);
				offset += 2 * sizeof(float);
			}
			if (mTangents.size() > 0) {
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
				offset += 3 * sizeof(float);
			}
			if (mBitangents.size() > 0) {
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
				offset += 3 * sizeof(float);
			}
		}
		else {
			size_t offset = 0;

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);
			offset += mPositions.size() * 3 * sizeof(float);
			if (mNormals.size() > 0) {
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);
				offset += mNormals.size() * 3 * sizeof(float);
			}
			if (mUVs.size() > 0) {
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)offset);
				offset += mUVs.size() * 2 * sizeof(float);
			}
			if (mTangents.size() > 0) {
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);
				offset += mTangents.size() * 3 * sizeof(float);
			}
			if (mBitangents.size() > 0) {
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);
				offset += mBitangents.size() * 3 * sizeof(float);
			}
		}

		glBindVertexArray(0);
	}

}

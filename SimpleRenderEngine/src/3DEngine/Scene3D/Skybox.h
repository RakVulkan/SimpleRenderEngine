#pragma once

#include <3DEngine/Shader.h>
#include <Platform/Window.h>
#include <3DEngine/Camera/Camera.h>
#include <3DEngine/Renderer/GLState.h>
#include <3DEngine/mesh/common/Cube.h>
#include <Utilities/Loaders/TextureLoader.h>

namespace RenderEngine {

	class Skybox {
	public:
		Skybox(const std::vector<std::string>& inFilePaths);
		~Skybox();

		void Draw(ICamera* inCamera);

		Cubemap* getSkyboxCubemap() { return mSkyboxCubemap; }
	private:
		Shader* mSkyboxShader;
		GLState* mGLState;
		
		Cube mCubeObject;
		Cubemap* mSkyboxCubemap;
	};

}

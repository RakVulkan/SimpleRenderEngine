#pragma once

#include <3DEngine/Scene3D/Scene3D.h>
#include <Platform/Window.h>
#include <3DEngine/Camera/Camera.h>
#include <3DEngine/Lights/LightManager.h>
#include <3DEngine/Renderer/GLState.h>
#include <3DEngine/Renderer/SceneObjectRenderer.h>
#include <3DEngine/Scene3D/RenderableSceneObject.h>
#include <Utilities/Loaders/TextureLoader.h>
#include <3DEngine/Scene3D/Skybox.h>

namespace RenderEngine {
	
	class Scene3D {
	public:
		Scene3D(Window* inWindow);
		~Scene3D();

		void onUpdate(float inDeltaTime);
		void addSceneObjectsToRenderer();

		inline SceneObjectRenderer* getSceneObjectRenderer() { return &mSceneObjectRenderer; }		
		inline LightManager* getDynamicLightManager() { return mLightManager; }		
		inline Camera* getCamera() { return &mSceneCamera; }
		inline Skybox* getSkybox() { return mSkybox; }

	private:
		void init();

	private:
		// Global Data
		GLState *mGLState;

		// Scene Specific Data
		Camera mSceneCamera;
		Skybox* mSkybox;
		SceneObjectRenderer mSceneObjectRenderer;
		LightManager* mLightManager;		
		std::vector<RenderableSceneObject*> mRenderableSceneObjects;
	};

}

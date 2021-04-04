#include<pch.h>
#include<Platform/Window.h>
#include<3DEngine/Scene3D/Scene3D.h>
#include<3DEngine/Renderer/Renderer.h>
#include<Utilities/Time.h>

int main()
{   
	RenderEngine::Window lWindow("PBR", WINDOW_WIDTH, WINDOW_HEIGHT);
	RenderEngine::TextureLoader::initializeDefaultTextures();
	RenderEngine::Scene3D lScene(&lWindow);
	RenderEngine::Renderer lRenderer(&lScene);
	RenderEngine::Time lDeltaTime;

	// Initialize the renderer
	lRenderer.init();

	while (!lWindow.closed()) {
		lDeltaTime.update();
		RenderEngine::Window::bind();
		RenderEngine::Window::clear();

		lScene.onUpdate(static_cast<float>(lDeltaTime.getDeltaTime()));
		lRenderer.render();

		// Window and input updating
		lWindow.update();
	}

	return 0;
}
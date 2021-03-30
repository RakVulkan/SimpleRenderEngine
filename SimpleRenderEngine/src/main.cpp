#include<pch.h>
#include<Platform/Window.h>

int main()
{   
	RenderEngine::Window lWindow("Graphics Engine", WINDOW_WIDTH, WINDOW_HEIGHT);

	while (!lWindow.closed()) {

		// Window and input updating
		lWindow.update();
	}

	return 0;
}
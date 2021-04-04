#pragma once

namespace RenderEngine {

	struct Time {
	private:
		GLdouble lastFrame;
		GLdouble delta;
	public:
		Time();

		void update();

		// Getters
		inline GLdouble getDeltaTime() const { return delta; }
	};

}

#include "GameEngine.hpp"

namespace GameEngine
{
	void Initialise()
	{
		// initialise SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		// Tell SDL that we want a double buffered window
		// to prevent screen tear
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}
}
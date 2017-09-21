#ifndef GAME_ENGINE_GL_TEXTURE_HPP
#define GAME_ENGINE_GL_TEXTURE_HPP

#include <GL/glew.h>

namespace GameEngine
{
	namespace Rendering
	{
		class GLTexture
		{
		public:
			GLuint ID;
			int Width;
			int Height;
		};
	}
}

#endif
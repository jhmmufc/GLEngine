#ifndef GAME_ENGINE_RESOURCE_MANAGER_HPP
#define GAME_ENGINE_RESOURCE_MANAGER_HPP

#include "TextureManager.hpp"

namespace GameEngine
{
	namespace ResourceManagement
	{
		class ResourceManager
		{
		public:
			Rendering::GLTexture& GetTexture(const std::string& path);
		private:
			TextureManager m_textureManager;
		};
	}
}

#endif
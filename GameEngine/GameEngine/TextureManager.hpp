#ifndef GAME_ENGINE_TEXTURE_MANAGER_HPP
#define GAME_ENGINE_TEXTURE_MANAGER_HPP

#include "Private/Utility.hpp"
#include "ImageLoader.hpp"
#include "GLTexture.hpp"

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <mutex>

namespace GameEngine
{
	namespace ResourceManagement
	{
		class TextureManager
		{
		public:
			Rendering::GLTexture GetTexture(const std::string& file_name);
		private:
			std::map<std::string, Rendering::GLTexture> m_textureMap;
			std::mutex m_textureMutex;
		};
	}
}

#endif
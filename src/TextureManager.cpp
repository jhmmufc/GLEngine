#include "TextureManager.hpp"

namespace GameEngine
{
	namespace ResourceManagement
	{
		Rendering::GLTexture TextureManager::GetTexture(const std::string& file_name)
		{
			auto found = m_textureMap.find(file_name);

			if (found != m_textureMap.end())
			{
				return found->second;
			}

			auto texture = Rendering::GLTexture();

			texture = Rendering::ImageLoader::LoadPNG(file_name);

			auto inserted = m_textureMap.insert(std::make_pair(file_name, texture));

			assert(inserted.second);

			return m_textureMap[file_name];
		}
	}
}
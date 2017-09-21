#include "ResourceManager.hpp"

namespace GameEngine
{
	namespace ResourceManagement
	{
		Rendering::GLTexture ResourceManager::GetTexture(const std::string& path)
		{
			return m_textureManager.GetTexture(path);
		}
	}
}
#ifndef GAME_ENGINE_UTILITY_HPP
#define GAME_ENGINE_UTILITY_HPP

#include <string>

namespace GameEngine
{
	namespace Private
	{
		namespace Utility
		{
			namespace IO
			{
				bool DoesFileExist(const std::string& filename);
			}
		}
	}
}

#endif
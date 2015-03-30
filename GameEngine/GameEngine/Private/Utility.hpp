#ifndef GAME_ENGINE_UTILITY_HPP
#define GAME_ENGINE_UTILITY_HPP

#include <string>
#include <vector>

namespace GameEngine
{
	namespace Private
	{
		namespace Utility
		{
			namespace IO
			{
				bool ReadFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
			}

			namespace Error
			{
				void FatalError(const std::string& errorString);
			}
		}
	}
}

#endif
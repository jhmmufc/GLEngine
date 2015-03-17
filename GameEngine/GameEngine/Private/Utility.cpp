#include "Utility.hpp"

#include <fstream>

namespace GameEngine
{
	namespace Private
	{
		namespace Utility
		{
			namespace IO
			{
				bool DoesFileExist(const std::string& filename)
				{
					std::ifstream infile(filename);
					return infile.good();
				}
			}
		}
	}
}
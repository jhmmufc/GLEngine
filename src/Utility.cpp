#include "Utility.hpp"

#include <iostream>
#include <fstream>

namespace GameEngine
{
	namespace Private
	{
		namespace Utility
		{
			namespace IO
			{
				bool ReadFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer)
				{
					std::ifstream file(filePath, std::ios::binary);

					if (file.fail())
					{
						std::cerr << "Could not load file " + filePath << std::endl;
						return false;
					}

					// Seek to the end of the file
					file.seekg(0, std::ios::end);

					// get the file size 
					int fileSize = static_cast<int>(file.tellg());

					// Seek back to the start
					file.seekg(0, std::ios::beg);

					// Reduce the file size by the length of any headr bytes
					fileSize -= static_cast<int>(file.tellg());

					// Resize the buffer to the size of the file
					buffer.resize(fileSize);

					// read the buffer into the file
					// This is a pointer to a char array 
					file.read(reinterpret_cast<char*>(&buffer[0]), fileSize);

					// No need to close the file as it does it itself
					// but sometimes worth doing anyway
					file.close();

					return true;
				}
			}

			namespace Error
			{
				void FatalError(const std::string& errorString)
				{
					// Print the error message
					std::cout << errorString << std::endl;
					std::cout << "Enter enter key to quit...." << std::endl;
					
					// Wait for the user the hit the enter key
					std::string temp;
					std::getline(std::cin, temp);
					
					// Exit with a code of -1 so we know something is wrong
					std::exit(-1);
				}
			}
		}
	}
}
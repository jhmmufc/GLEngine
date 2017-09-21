#ifndef GAME_ENGINE_IMAGE_LOADER_HPP
#define GAME_ENGINE_IMAGE_LOADER_HPP

#include "Utility.hpp"
#include "GLTexture.hpp"
#include "PicoPNG.hpp"

#include <string>

namespace GameEngine
{
	namespace Rendering
	{
		namespace ImageLoader
		{
			inline GLTexture LoadPNG(const std::string& filePath)
			{
				GLTexture texture = {};

				std::vector<unsigned char> in;
				std::vector<unsigned char> out;

				unsigned long width, height;

				if (!Private::Utility::IO::ReadFileToBuffer(filePath, in))
				{
					Private::Utility::Error::FatalError("Failed to load PNG file to buffer!");
				}

				int status = PicoPNG::DecodePNG(out, width, height, &in[0], in.size());

				if (status != 0)
				{
					Private::Utility::Error::FatalError("DecodePNG with error " + std::to_string(status));
				}

				glGenTextures(1, &texture.ID);

				glBindTexture(GL_TEXTURE_2D, texture.ID);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				glGenerateMipmap(GL_TEXTURE_2D);

				glBindTexture(GL_TEXTURE_2D, 0);

				texture.Width = width;
				texture.Height = height;

				return texture;
			}
		}
	}
}

#endif

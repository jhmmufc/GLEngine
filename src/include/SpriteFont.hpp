#ifndef GAME_ENGINE_SPRITE_FONT_HPP
#define GAME_ENGINE_SPRITE_FONT_HPP

#include <SDL/SDL_ttf.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "Vertex.hpp"

namespace GameEngine 
{
	namespace Rendering 
	{
		class GLTexture;
		class SpriteBatch;

		struct CharGlyph 
		{
			char Character;
			glm::vec4 UVRect;
			glm::vec2 Size;
		};

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

		/// For text justification
		enum class Justification 
		{
			LEFT, MIDDLE, RIGHT
		};

		class SpriteFont 
		{
		public:
			SpriteFont() = default;
			SpriteFont(const std::string& font, int size, char cs, char ce);
			SpriteFont(const std::string& font, int size) :
				SpriteFont(font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR) 
			{
			}

			void Load(const std::string& font, int size, char cs = FIRST_PRINTABLE_CHAR, char ce = LAST_PRINTABLE_CHAR);

			~SpriteFont()
			{
				if (m_texID != 0)
				{
					glDeleteTextures(1, &m_texID);
					m_texID = 0;
				}
			}

			int GetFontHeight() const 
			{
				return m_fontHeight;
			}

			/// Measures the dimensions of the text
			glm::vec2 Measure(const std::string& s);

			/// Draws using a spritebatch
			void Draw(SpriteBatch& batch, const std::string& s, const glm::vec2& position, glm::vec2 scaling,
				float depth, ColourRGBA8 tint, Justification just = Justification::LEFT);
		private:
			static std::vector<std::vector<int>> CreateRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);

			int m_regStart, m_regLength;
			std::vector<CharGlyph> m_glyphs;
			int m_fontHeight;

			unsigned int m_texID;
		};
	}
}

#endif
#include "SpriteFont.hpp"
#include "SpriteBatch.hpp"
#include "Private/Utility.hpp"

#include <SDL/SDL.h>

int ClosestPow2(int i)
{
	i--;
	int pi = 1;
	while (i > 0) 
	{
		i >>= 1;
		pi <<= 1;
	}
	return pi;
}

#define MAX_TEXTURE_RES 4096

namespace GameEngine 
{
	namespace Rendering
	{
		SpriteFont::SpriteFont(const std::string& font, int size, char cs, char ce) 
		{
			Load(font, size, cs, ce);
		}

		void SpriteFont::Load(const std::string& font, int size, char cs, char ce)
		{
			// Initialize SDL_ttf
			if (!TTF_WasInit())
			{
				TTF_Init();
			}

			TTF_Font* f = TTF_OpenFont(font.c_str(), size);

			if (f == nullptr)
			{
				Private::Utility::Error::FatalError("Failed to open TTF font + " + font);
			}

			m_fontHeight = TTF_FontHeight(f);
			m_regStart = cs;
			m_regLength = ce - cs + 1;
			int padding = size / 8;

			// First neasure all the regions
			std::vector<glm::ivec4> glyphRects;
			glyphRects.resize(m_regLength);

			int i = 0, advance;
			for (char c = cs; c <= ce; c++)
			{
				TTF_GlyphMetrics(f, c, &glyphRects[i].x, &glyphRects[i].z, &glyphRects[i].y, &glyphRects[i].w, &advance);
				glyphRects[i].z -= glyphRects[i].x;
				glyphRects[i].x = 0;
				glyphRects[i].w -= glyphRects[i].y;
				glyphRects[i].y = 0;
				i++;
			}

			// Find best partitioning of glyphs
			int rows = 1, w, h, bestWidth = 0, bestHeight = 0, area = MAX_TEXTURE_RES * MAX_TEXTURE_RES, bestRows = 0;
			std::vector<std::vector<int>> bestPartition;

			while (rows <= m_regLength)
			{
				h = rows * (padding + m_fontHeight) + padding;
				auto gr = CreateRows(&glyphRects[0], m_regLength, rows, padding, w);

				// Desire a power of 2 texture
				w = ClosestPow2(w);
				h = ClosestPow2(h);

				// A texture must be feasible
				if (w > MAX_TEXTURE_RES || h > MAX_TEXTURE_RES)
				{
					rows++;
					continue;
				}

				// Check for minimal area
				if (area >= w * h)
				{
					bestPartition = gr;
					bestWidth = w;
					bestHeight = h;
					bestRows = rows;
					area = bestWidth * bestHeight;
					rows++;
				}
				else
				{
					break;
				}
			}

			// Can a bitmap font be made?
			if (bestPartition.empty())
			{
				Private::Utility::Error::FatalError("Failed to Map TTF font to texture. Try lowering resolution: " + font);
			}

			// Create the texture
			glGenTextures(1, &m_texID);
			glBindTexture(GL_TEXTURE_2D, m_texID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bestWidth, bestHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			// Now draw all the glyphs
			SDL_Color fg = { 255, 255, 255, 255 };
			int ly = padding;
			for (int ri = 0; ri < bestRows; ri++)
			{
				int lx = padding;
				for (size_t ci = 0; ci < bestPartition[ri].size(); ci++)
				{
					int gi = bestPartition[ri][ci];

					SDL_Surface* glyphSurface = TTF_RenderGlyph_Blended(f, (char)(cs + gi), fg);

					// Pre-multiplication occurs here
					unsigned char* sp = (unsigned char*)glyphSurface->pixels;
					int cp = glyphSurface->w * glyphSurface->h * 4;
					for (int i = 0; i < cp; i += 4)
					{
						float a = sp[i + 3] / 255.0f;
						sp[i] *= static_cast<unsigned char>(a);
						sp[i + 1] = sp[i];
						sp[i + 2] = sp[i];
					}

					// Save glyph image and update coordinates
					glTexSubImage2D(GL_TEXTURE_2D, 0, lx, bestHeight - ly - 1 - glyphSurface->h, glyphSurface->w, glyphSurface->h, GL_BGRA, GL_UNSIGNED_BYTE, glyphSurface->pixels);
					glyphRects[gi].x = lx;
					glyphRects[gi].y = ly;
					glyphRects[gi].z = glyphSurface->w;
					glyphRects[gi].w = glyphSurface->h;

					SDL_FreeSurface(glyphSurface);
					glyphSurface = nullptr;

					lx += glyphRects[gi].z + padding;
				}
				ly += m_fontHeight + padding;
			}

			// Draw the unsupported glyph
			int rs = padding - 1;
			std::vector<int> pureWhiteSquare;
			pureWhiteSquare.resize(rs * rs);
			memset(&pureWhiteSquare[0], 0xffffffff, rs * rs * sizeof(int));
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rs, rs, GL_RGBA, GL_UNSIGNED_BYTE, &pureWhiteSquare[0]);

			// Set some texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			// Create spriteBatch glyphs
			m_glyphs.resize(m_regLength + 1);

			for (i = 0; i < m_regLength; i++)
			{
				m_glyphs[i].Character = (char)(cs + i);
				m_glyphs[i].Size = glm::vec2(glyphRects[i].z, glyphRects[i].w);
				m_glyphs[i].UVRect = glm::vec4(
					(float)glyphRects[i].x / (float)bestWidth,
					(float)glyphRects[i].y / (float)bestHeight,
					(float)glyphRects[i].z / (float)bestWidth,
					(float)glyphRects[i].w / (float)bestHeight
					);
			}
			m_glyphs[m_regLength].Character = ' ';
			m_glyphs[m_regLength].Size = m_glyphs[0].Size;
			m_glyphs[m_regLength].UVRect = glm::vec4(0, 0, (float)rs / (float)bestWidth, (float)rs / (float)bestHeight);

			glBindTexture(GL_TEXTURE_2D, 0);
			TTF_CloseFont(f);
		}

		std::vector<std::vector<int>> SpriteFont::CreateRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w) {
			// Blank initialize
			std::vector<std::vector<int>> l;
			l.resize(r);
			std::vector<int> cw;
			cw.resize(r);

			for (int i = 0; i < r; i++) 
			{
				cw[i] = padding;
			}

			// Loop through all glyphs
			for (int i = 0; i < rectsLength; i++) 
			{
				// Find row for placement
				int ri = 0;
				for (int rii = 1; rii < r; rii++)
					if (cw[rii] < cw[ri]) ri = rii;

				// Add width to that row
				cw[ri] += rects[i].z + padding;

				// Add glyph to the row list
				l[ri].push_back(i);
			}

			// Find the max width
			w = 0;
			for (int i = 0; i < r; i++) 
			{
				if (cw[i] > w) w = cw[i];
			}

			return l;
		}

		glm::vec2 SpriteFont::Measure(const std::string& s) 
		{
			glm::vec2 size(0, m_fontHeight);
			float cw = 0;
			for (int si = 0; s[si] != 0; si++) 
			{
				char c = s[si];
				if (s[si] == '\n')
				{
					size.y += m_fontHeight;
					if (size.x < cw)
					{
						size.x = cw;
					}
					cw = 0;
				}
				else 
				{
					// Check for correct glyph
					int gi = c - m_regStart;
					if (gi < 0 || gi >= m_regLength)
					{
						gi = m_regLength;
					}
					cw += m_glyphs[gi].Size.x;
				}
			}
			if (size.x < cw)
			{
				size.x = cw;
			}
			return size;
		}

		void SpriteFont::Draw(SpriteBatch& batch, const std::string& s, const glm::vec2& position, glm::vec2 scaling,
			float depth, ColourRGBA8 tint, Justification just /* = Justification::LEFT */) 
		{
			glm::vec2 tp = position;
			tp.y += m_fontHeight / 2.0f;
			scaling.y *= -1.0f;
			// Apply justification
			if (just == Justification::MIDDLE) 
			{
				tp.x -= Measure(s.c_str()).x * scaling.x / 2;
			}
			else if (just == Justification::RIGHT) 
			{
				tp.x -= Measure(s.c_str()).x * scaling.x;
			}
			for (int si = 0; s[si] != 0; si++) 
			{
				char c = s[si];
				if (s[si] == '\n') 
				{
					tp.y += m_fontHeight * scaling.y;
					tp.x = position.x;
				}
				else 
				{
					// Check for correct glyph
					int gi = c - m_regStart;
					if (gi < 0 || gi >= m_regLength)
						gi = m_regLength;

					glm::vec4 destRect(tp, m_glyphs[gi].Size * scaling);
					batch.Draw(destRect, m_glyphs[gi].UVRect, m_texID, depth, tint);
					tp.x += m_glyphs[gi].Size.x * scaling.x;
				}
			}
		}
	}
}
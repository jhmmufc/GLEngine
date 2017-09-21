#ifndef GAME_ENGINE_SPRITE_BATCH_HPP
#define GAME_ENGINE_SPRITE_BATCH_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Sprite.hpp"
#include "Vertex.hpp"

namespace GameEngine
{
	namespace Rendering
	{
		// Determines how we should sort the glyphs
		enum class GlyphSortType 
		{
			NONE,
			FRONT_TO_BACK,
			BACK_TO_FRONT,
			TEXTURE
		};

		// A glyph is a single quad. These are added via SpriteBatch::draw
		class Glyph 
		{
		public:
			Glyph() {};
			Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);
			Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, float angle);

			GLuint Texture;
			float Depth;

			Vertex TopLeft;
			Vertex BottomLeft;
			Vertex TopRight;
			Vertex BottomRight;
		private:
			// Rotates a point about (0,0) by angle
			glm::vec2 RotatePoint(const glm::vec2& pos, float angle);
		};

		// Each render batch is used for a single draw call
		class RenderBatch 
		{
		public:
			RenderBatch(GLuint offset, GLuint numVertices, GLuint texture) : Offset(offset),
				NumVertices(numVertices), Texture(texture)
			{
			}
			GLuint Offset;
			GLuint NumVertices;
			GLuint Texture;
		};

		// The SpriteBatch class is a more efficient way of drawing sprites
		class SpriteBatch
		{
		public:
			SpriteBatch();
			~SpriteBatch();

			// Initializes the spritebatch
			void Init();

			// Begins the spritebatch
			void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

			// Ends the spritebatch
			void End();

			// Adds a sprite to the spritebatch
			void Draw(const Sprite& sprite);
			// Adds a glyph to the spritebatch
			void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);
			// Adds a glyph to the spritebatch with rotation
			void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, float angle);
			// Adds a glyph to the spritebatch with rotation
			void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, const glm::vec2& dir);

			// Renders the entire SpriteBatch to the screen
			void RenderBatches();

		private:
			// Creates all the needed RenderBatches
			void CreateRenderBatches();

			// Generates our VAO and VBO
			void CreateVertexArray();

			// Sorts glyphs according to _sortType
			void SortGlyphs();

			// Comparators used by sortGlyphs()
			static bool CompareFrontToBack(Glyph* a, Glyph* b);
			static bool CompareBackToFront(Glyph* a, Glyph* b);
			static bool CompareTexture(Glyph* a, Glyph* b);

			GLuint m_vbo;
			GLuint m_vao;

			GlyphSortType m_sortType;

			std::vector<Glyph*> m_glyphPointers; ///< This is for sorting
			std::vector<Glyph> m_glyphs; ///< These are the actual glyphs
			std::vector<RenderBatch> m_renderBatches;
		};
	}
}

#endif
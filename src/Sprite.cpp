#include "Sprite.hpp"

namespace GameEngine
{
	namespace Rendering
	{
		Sprite::Sprite(const std::string& filename, GameEngine::GameContext& context, const glm::vec4& destRect, const glm::vec4& uvRect, float depth, float angle, const GameEngine::Rendering::ColourRGBA8& colour, bool flip) :
			m_texture(context.GetResourceManager().GetTexture(filename)),
			m_destRect(destRect),
			m_uvRect(uvRect),
			m_depth(depth),
			m_colour(colour),
			m_angle(angle)
		{
			if (flip)
			{
				Flip();
			}
		}

		void Sprite::Load(const std::string& filename, GameEngine::GameContext& context, const glm::vec4& destRect, const glm::vec4& uvRect, float depth, float angle, const GameEngine::Rendering::ColourRGBA8& colour, bool flip)
		{
			m_texture = context.GetResourceManager().GetTexture(filename);
			m_destRect = destRect;
			m_uvRect = uvRect;
			m_depth = depth;
			m_angle = angle;
			m_colour = ColourRGBA8(colour);

			if (flip)
			{
				Flip();
			}
		}

		void Sprite::Flip()
		{
			m_uvRect.z *= -1.0f;
			m_uvRect.w *= -1.0f;
		}
	}
}
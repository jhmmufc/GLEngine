//#include "Sprite.hpp"
//#include "Vertex.hpp"
//
//namespace GameEngine
//{
//	namespace Rendering
//	{
//		Sprite::Sprite(const std::string& filename, GameContext& context, const glm::vec4& destRect, const glm::vec4& uvRect, float depth, const ColourRGBA8& colour) :
//			m_texture(context.GetResourceManager().GetTexture(filename)),
//			m_destRect(destRect),
//			m_uvRect(uvRect),
//			m_depth(depth),
//			m_colour(colour)
//		{
//
//		}
//
//		void Sprite::Load(const std::string& filename, GameContext& context, const glm::vec4& destRect, const glm::vec4& uvRect, float depth, const ColourRGBA8& colour)
//		{
//			m_texture = context.GetResourceManager().GetTexture(filename);
//			m_destRect = destRect;
//			m_uvRect = uvRect;
//			m_depth = depth;
//			m_colour = ColourRGBA8(colour);
//		}
//
//		void Sprite::Flip()
//		{
//			m_uvRect.z *= -1.0f;
//			m_uvRect.w *= -1.0f;
//		}
//	}
//}
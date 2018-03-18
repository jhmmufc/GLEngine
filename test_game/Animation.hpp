#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <Sprite.hpp>
#include <SpriteBatch.hpp>
#include "TileSheet.hpp"

class Animation
{
public:
    Animation(GameEngine::GameContext& context, const std::string& texture, const glm::vec2& position, float frameWidth, float frameHeight, int rows, int columns, float frameTime, float scale, bool loop) :
        m_pos(position),
        m_frameWidth(frameWidth),
        m_frameHeight(frameHeight),
        m_frameCount(rows * columns),
        m_frameTime(frameTime),
        m_scale(scale),
        m_looping(loop),
        m_elapsedTime(0),
        m_currentFrame(0),
        m_active(true),
        m_texture(context.GetResourceManager().GetTexture(texture), glm::ivec2(rows, columns)),
        m_flippedX(false),
        m_flippedY(false)
    {
        
    }

    template<typename T>
    auto Clamp(T val, T min, T max) -> T
    {
        return glm::clamp(val, min, max);
    }

    auto Move(const glm::vec2& pos, const int screenWidth, const int screenHeight, bool clamp) -> void
    {
        m_pos += pos;

        if (clamp)
        {
            m_pos.x = Clamp<float>(m_pos.x, 0, screenWidth - m_frameWidth);
            m_pos.y = Clamp<float>(m_pos.y, 0, screenHeight - m_frameHeight);
        }
    }

    auto Update(float elapsedTime) -> void
    {
        if(!m_active)
        {
            return;
        }

        m_elapsedTime += elapsedTime;

        if(m_elapsedTime > m_frameTime)
        {
            ++m_currentFrame;

            if(m_currentFrame ==  m_frameCount)
            {
                m_currentFrame = 0;

                if(!m_looping)
                {
                    m_active = false;
                }
            }

            m_elapsedTime = 0;
        }
    }

    auto Draw(GameEngine::Rendering::SpriteBatch& spriteBatch) -> void
    {
        if (m_active)
        {
            spriteBatch.Draw(glm::vec4(m_pos, m_frameWidth, m_frameHeight), 
                Uvs(), 
                m_texture.Id(), 
                0.0f, 
                GameEngine::Rendering::ColourRGBA8(255, 255, 255, 255));
        }
    }

    auto Flip(bool x, bool y) -> void
    {
        m_flippedX = x;
        m_flippedY = y;
    }

    auto Position() const
    {
        return m_pos;
    }

    auto Width() const
    {
        return m_frameWidth;
    }

    auto Height() const
    {
        return m_frameHeight;
    }

    glm::vec4 GetBoundingBox() const
    {
        return glm::vec4(Position().x, Position().y, Position().x + Width(), Position().y + Height());
    }

    bool Collides(const glm::vec4& B) const
    {
        const auto& A = GetBoundingBox();

        bool xOverlap = ValueInRange(A.x, B.x, B.z) ||
            ValueInRange(B.x, A.x, A.z);

        bool yOverlap = ValueInRange(A.y, B.y, B.w) ||
            ValueInRange(B.y, A.y, A.w);

        return xOverlap && yOverlap;
    }

private:
    bool ValueInRange(int value, int min, int max) const
    {
        return (value >= min) && (value <= max);
    }

    auto Uvs() -> glm::vec4
    {
        auto uvs = m_texture.GetUVs(m_currentFrame);

        if (m_flippedX)
        {
            uvs.z *= -1.0f;
        }

        if(m_flippedY)
        {
            uvs.w *= -1.0f;
        }

        return uvs;
    }

    float m_frameWidth;
    float m_frameHeight;
    float m_elapsedTime;
    bool m_active;
    float m_scale;
    bool m_looping;
    float m_frameTime;
    unsigned int m_frameCount;
    unsigned int m_currentFrame;
    glm::vec2 m_pos;
    TileSheet m_texture;
    glm::vec4 m_uvs;
    bool m_flippedX;
    bool m_flippedY;
};

#endif

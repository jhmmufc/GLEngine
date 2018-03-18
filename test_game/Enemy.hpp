#pragma once

#include "Animation.hpp"
#include <glm/detail/type_vec2.hpp>

class Enemy final
{
public:
    Enemy(GameEngine::GameContext& context, const std::string& textureName, const glm::vec2& startPos) : 
    m_sprite(context,
        textureName,
        startPos,
        47.0f, 61.0f, 8, 1, 0.1f, 1.0f, true),
        m_active(true),
        m_health(10),
        m_damage(10),
        m_speed(6.0f),
        m_value(100)
    {
        m_sprite.Flip(false, true);
        
    }
    auto Update(const float elapsedTime) -> void
    {
        m_sprite.Update(elapsedTime);
    }

    auto Move()
    {
        m_sprite.Move(glm::vec2(-m_speed, 0.0f), 0, 0, false);

        if(m_sprite.Position().x < -m_sprite.Width() || m_health <= 0)
        {
            m_active = false;
        }
    }

    auto Draw(GameEngine::Rendering::SpriteBatch& spriteBatch) -> void
    {
        m_sprite.Draw(spriteBatch);
    }

    auto IsActive() const
    {
        return m_active;
    }

    glm::vec4 GetBoundingBox() const
    {
        return m_sprite.GetBoundingBox();
    }

    void Kill()
    {
        m_active = false;
    }

    auto Damage() const
    {
        return m_damage;
    }

private:
    Animation m_sprite;
    bool m_active;
    int m_health;
    int m_value;
    int m_damage;
    float m_speed;
};

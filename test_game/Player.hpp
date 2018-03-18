#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SpriteBatch.hpp>
#include <iostream>
#include "Animation.hpp"

class Player final
{
public:
    Player(GameEngine::GameContext& context, const std::string& textureName, const glm::vec2& startPos) :
        m_sprite(context,
            textureName,
            startPos,
            115.f, 69.0f, 8, 1, 0.1f, 1.0f, true),
            m_active(true),
            m_health(100)
    {
       
    }

    auto HandleInput(ge::Input::InputManager& inputManager)
    {
        m_direction = glm::vec2();

        if (inputManager.IsKeyPressed(SDLK_w))
        {
            m_direction.y = -1;
        }
        else if (inputManager.IsKeyPressed(SDLK_s))
        {
            m_direction.y = 1;
        }

        if (inputManager.IsKeyPressed(SDLK_a))
        {
            m_direction.x = -1;

            m_sprite.Flip(true, true);
        }
        else if (inputManager.IsKeyPressed(SDLK_d))
        {
            m_direction.x = 1;

            m_sprite.Flip(false, false);
        }
    }

    auto Direction() const
    {
        return m_direction;
    }

    auto Move(const glm::vec2& pos, const int screenWidth, const int screenHeight) -> void
    {
        m_sprite.Move(pos * Direction(), screenWidth, screenHeight, true);
    }

    auto Update(const float elapsedTime) -> void
    {
        m_sprite.Update(elapsedTime);
    }

    auto Draw(GameEngine::Rendering::SpriteBatch& spriteBatch) -> void
    {
        m_sprite.Draw(spriteBatch);
    }

    glm::vec4 GetBoundingBox() const
    {
        return m_sprite.GetBoundingBox();
    }

    bool Collides(const glm::vec4& rect) const
    {
        return m_sprite.Collides(rect);
    }

    void Hurt(int damage)
    {
        m_health -= damage;
    }
private:
    Animation m_sprite;
    bool m_active;
    int m_health;
    glm::vec2 m_direction;
};

#endif

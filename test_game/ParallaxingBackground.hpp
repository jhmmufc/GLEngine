#pragma once

#include <vector>
#include <GameContext.hpp>
#include <SpriteBatch.hpp>

class ParallaxingBackground
{
public:
    ParallaxingBackground(GameEngine::GameContext& context, const std::string& texture, int screenWidth, int screenHeight, int speed) : 
        m_sprite(texture, context, glm::vec4(0, 0, screenWidth, screenHeight), 
            glm::vec4(0, 0, 1, 1), 0.0f, 0.0f, GameEngine::Rendering::ColourRGBA8(255, 255, 255, 255), false),
        m_speed(speed),
        m_positions()
    {
        for(int i = 0; i < screenWidth / m_sprite.Texture().Width + 1; i++)
        {
            m_positions.emplace_back(glm::vec2(i * m_sprite.Texture().Width, 0));
        }
    }

    auto Update() -> void
    {
        for (auto& position : m_positions)
        {
            position.x += m_speed;

            if(m_speed <= 0)
            {
                if(position.x <= -m_sprite.Texture().Width)
                {
                    position.x = m_sprite.Texture().Width * (m_positions.size() - 1);
                }
            }
            else
            {
                if(position.x >= m_sprite.Texture().Width * (m_positions.size() - 1))
                {
                    position.x -= m_sprite.Texture().Width;
                }
            }
        }
    }

    auto Draw(GameEngine::Rendering::SpriteBatch& spriteBatch)
    {
        for(auto& position : m_positions)
        {
            m_sprite.SetPosition(position);
            spriteBatch.Draw(m_sprite);
        }
    }

private:
    GameEngine::Rendering::Sprite m_sprite;
    std::vector<glm::vec2> m_positions;
    int m_speed;
};

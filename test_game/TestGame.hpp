#ifndef GAME_HPP
#define GAME_HPP

#include <Game.hpp>

class TestGame : public Game
{
public:
    TestGame();
    ~TestGame() = default;
protected:
    virtual void OnInitialise() final;
    virtual void OnUpdate(const float elapsedTime) final;
    virtual void OnInput(ge::Input::InputManager& inputManager) final;
    virtual void OnDraw() final;
private:
    // A sprite
    ge::Rendering::Sprite m_sprite;
    glm::vec2 m_spriteDir;
};

#endif
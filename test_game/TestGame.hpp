#ifndef GAME_HPP
#define GAME_HPP

#include <Game.hpp>
#include "Player.hpp"
#include "ParallaxingBackground.hpp"
#include "Enemy.hpp"
#include <random>

class TestGame : public Game
{
public:
    TestGame();
    ~TestGame() = default;
protected:
    virtual void OnUpdate(const float elapsedTime) final;
    virtual void OnInput(ge::Input::InputManager& inputManager) final;
    virtual void OnDraw() final;
private:
    void AddEnemy();
    void UpdateEnemies(const float elapsedTime);
    void UpdateCollision(Enemy& enemy);

    Player m_player;
    std::vector<ParallaxingBackground> m_backgrounds;
    std::vector<Enemy> m_enemies;

    std::random_device rd;
};

#endif
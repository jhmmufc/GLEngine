#include "TestGame.hpp"

TestGame::TestGame() 
        : Game("Shooter", 800, 600),
        m_player(Context, 
            "Textures/shipAnimation.png", 
            glm::vec2(10, ScreenHeight / 2))
{
    m_backgrounds.emplace_back(Context, "Textures/mainbackground.png", ScreenWidth, ScreenHeight, 0);
    m_backgrounds.emplace_back(Context, "Textures/bgLayer1.png", ScreenWidth, ScreenHeight, -1);
    m_backgrounds.emplace_back(Context, "Textures/bgLayer2.png", ScreenWidth, ScreenHeight , -2);
}

void TestGame::OnInput(ge::Input::InputManager& inputManager)
{
	// change the sprite direction depending on what key is pressed
    m_player.HandleInput(inputManager);
}

void TestGame::OnUpdate(const float elapsedTime)
{
    m_player.Update(elapsedTime);

	// update the player position
    m_player.Move(glm::vec2(200.0f * elapsedTime), ScreenWidth, ScreenHeight);

    UpdateEnemies(elapsedTime);

    for(auto& background : m_backgrounds)
    {
        background.Update();
    }
}

void TestGame::OnDraw()
{
    SpriteBatch.Begin(GameEngine::Rendering::GlyphSortType::FRONT_TO_BACK);

    for (auto& background : m_backgrounds)
    {
        background.Draw(SpriteBatch);
    }

    for (auto& enemy : m_enemies)
    {
        enemy.Draw(SpriteBatch);
    }

    // Only render if we can be seen
    m_player.Draw(SpriteBatch);

	SpriteBatch.End();
}

void TestGame::AddEnemy()
{
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(100, ScreenHeight - 100);

    glm::vec2 position(ScreenWidth + 47 / 2, dist(mt));

    m_enemies.emplace_back(Enemy(Context, "Textures/mineAnimation.png", position));
}

void TestGame::UpdateEnemies(const float elapsedTime)
{
    static auto then = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());

    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());

    std::chrono::milliseconds dur(now - then);

    if(dur.count() > 1000)
    {
        then = now;

        AddEnemy();
    }

    for(auto& enemy : m_enemies)
    {
        enemy.Update(elapsedTime);
        enemy.Move();

        UpdateCollision(enemy);
    }

    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](const Enemy& enemy)
    {
        return !enemy.IsActive();
    }), m_enemies.end());
}

void TestGame::UpdateCollision(Enemy& enemy)
{
    if (m_player.Collides(enemy.GetBoundingBox()))
    {
        m_player.Hurt(enemy.Damage());

        enemy.Kill();
    }
}

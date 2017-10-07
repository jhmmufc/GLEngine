#include "TestGame.hpp"

TestGame::TestGame()
{

}

void TestGame::OnInitialise()
{
	// Initialise our sprite
	m_sprite.Load("Textures/test.png",
				  Context,
				  glm::vec4(0.0f, 0.0f, 32.0f, 32.0f),
				  glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, 0.0f,
				  ge::Rendering::ColourRGBA8(255, 255, 255, 255), true);
}

void TestGame::OnInput(ge::Input::InputManager& inputManager)
{
	// change the sprite direction depending on what key is pressed
	m_spriteDir = glm::vec2(0.0f);

	if (inputManager.IsKeyPressed(SDLK_w))
	{
		m_spriteDir.y = -1.0f;
	}
	else if (inputManager.IsKeyPressed(SDLK_s))
	{
		m_spriteDir.y = 1.0f;
	}

	if (inputManager.IsKeyPressed(SDLK_a))
	{
		m_spriteDir.x = -1.0f;
	}
	else if (inputManager.IsKeyPressed(SDLK_d))
	{
		m_spriteDir.x = 1.0f;
	}
}

void TestGame::OnUpdate(const float elapsedTime)
{
	// update the player position
	m_sprite.Move(m_spriteDir * 200.0f * elapsedTime);
}

void TestGame::OnDraw()
{
	SpriteBatch.Begin();

	// Only render if we can be seen
	if (Camera.IsBoxInView(m_sprite.GetPosition(), m_sprite.GetSize()))
	{
		SpriteBatch.Draw(m_sprite);
	}

	SpriteBatch.End();
}
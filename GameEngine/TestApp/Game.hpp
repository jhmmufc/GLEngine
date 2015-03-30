#ifndef GAME_HPP
#define GAME_HPP

#include <GameEngine/GameEngine.hpp>

class Game
{
public:
	Game();

	int Run();
private:
	void LoadShaders();

	void ProcessInput();
	void Update(float elapsedTime);
	void Render();

	bool m_running = true;

	int m_screenWidth = 800;
	int m_screenHeight = 600;

	// The context for our game, similiar to XNA ContentManager
	ge::GameContext m_gameContext;

	// Our games window
	ge::Rendering::Window m_window;

	// The texture program we use for shaders and rendering
	ge::Rendering::GLSLProgram m_textureProgram;

	// The camera for our game
	ge::Rendering::Camera m_camera;

	// The spritebatch for our game
	ge::Rendering::SpriteBatch m_spriteBatch;

	// A sprite
	ge::Rendering::Sprite m_sprite;
	glm::vec2 m_spriteDir;

	// to keep our game loop in time
	static const ge::Timing::Time TimePerFrame;
};

#endif
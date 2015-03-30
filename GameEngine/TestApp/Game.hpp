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
	void Update();
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
};

#endif
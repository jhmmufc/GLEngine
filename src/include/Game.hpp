#ifndef GAME_ENGINE_GAME_HPP
#define GAME_ENGINE_GAME_HPP

#include <GameEngine.hpp>

class Game
{
public:
	Game(const std::string& gameName, int screenWidth = 800, int screenHeight = 600);
    virtual ~Game() = default;
	int Run();
protected:
	virtual void OnUpdate(const float elapsedTime) = 0;
	virtual void OnInput(ge::Input::InputManager& inputManager) = 0;
	virtual void OnDraw() = 0;

	int ScreenWidth = 800;
	int ScreenHeight = 600;

	// The context for our game, similiar to XNA ContentManager
	ge::GameContext Context;

	// Our games window
	ge::Rendering::Window Window;

	// The texture program we use for shaders and rendering
	ge::Rendering::GLSLProgram TextureProgram;

	// The camera for our game
	ge::Rendering::Camera Camera;

	// The spritebatch for our game
	ge::Rendering::SpriteBatch SpriteBatch;
private:
	void LoadShaders();

	void ProcessInput();
	void Update(float elapsedTime);
	void Render();

	bool m_running = true;

	// to keep our game loop in time
	static const ge::Timing::Time TimePerFrame;
};

#endif
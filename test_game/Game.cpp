#include "Game.hpp"

// We wish to run our game at 60fps
const ge::Timing::Time Game::TimePerFrame = ge::Timing::Seconds(1.0f / 60.0f);

Game::Game() : 
	m_gameContext(),
	m_textureProgram(),
	m_window(),
	m_camera()
{
	// initialise our game engine
	ge::Initialise();

	// create a window
	m_window.CreateWindow("Game", m_screenWidth, m_screenHeight, ge::Rendering::WindowFlags::NONE);

	// Use a black background colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Initialise our camera
	m_camera.Initialise(m_screenWidth, m_screenHeight);

	// Initialise our spritebatch
	m_spriteBatch.Init();

	// Initialise our sprite
	m_sprite.Load("Textures/test.png", m_gameContext, glm::vec4(0.0f, 0.0f, 32.0f, 32.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, 0.0f, ge::Rendering::ColourRGBA8(255, 255, 255, 255), true);

	// Load our opengl shaders
	LoadShaders();
}

void Game::LoadShaders()
{
	// Compile our texture colour shader
	m_textureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	
	// Add attributes for colour, uv(texcoords) and position
	m_textureProgram.AddAttribute("vertexPosition");
	m_textureProgram.AddAttribute("vertexColor");
	m_textureProgram.AddAttribute("vertexUV");

	// get the program ready for using by linker the shaders 
	m_textureProgram.LinkShaders();
}

int Game::Run()
{
	// Start our game loop timer
	ge::Timing::Clock clock;

	// work out the time since our last update
	ge::Timing::Time timeSinceLastUpdate = ge::Timing::Time::Zero;

	while (m_running)
	{
		// Restart our timer
		ge::Timing::Time elapsedTime = clock.Restart();

		timeSinceLastUpdate += elapsedTime;

		// Process our input
		ProcessInput();

		// While we still have time we process all the input
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			// Keep updating while we have time
			Update(TimePerFrame.AsSeconds());
		}

		// finally we render our game
		Render();
	}

	return 0;
}

void Game::ProcessInput()
{
	SDL_Event evnt;

	std::vector<SDL_Event> events;

	// retrieve events until the function returns false
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			// If the type is quit, then quit the game
			m_running = false;
			break;
		}

		events.push_back(evnt);
	}

	// Add all the events to the event manager
	auto& inputManager = m_gameContext.GetInputManager();

	inputManager.Update(events);

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

void Game::Update(float elapsedTime)
{
	// update the player position
	m_sprite.Move(m_spriteDir * 200.0f * elapsedTime);

	// update our camera
	m_camera.Update();
}

void Game::Render()
{
	// Set the depth base to 1.0
	glClearDepth(1.0);

	// Clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind our texture program ready for rendering
	m_textureProgram.Bind();

	// Activate textures and send them to the shaders
	glActiveTexture(GL_TEXTURE0);

	// Make sure the shader uses texture 0
	GLint textureUniform = m_textureProgram.GetUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// Grab the camera matrix and send that to the shader
	GLint camUniform = m_textureProgram.GetUniformLocation("P");
	glUniformMatrix4fv(camUniform, 1, GL_FALSE, &m_camera.GetCameraMatrix()[0][0]);

	// DRAW SOME STUFF

	m_spriteBatch.Begin();

	// Only render if we can be seen
	if (m_camera.IsBoxInView(m_sprite.GetPosition(), m_sprite.GetSize()))
	{
		m_spriteBatch.Draw(m_sprite);
	}

	m_spriteBatch.End();

	m_spriteBatch.RenderBatches();

	// FINISH DRAWING

	// Unbind the texture program
	m_textureProgram.Unbind();

	// Swap our buffer and draw everything to the screen!
	m_window.SwapBuffer();
}
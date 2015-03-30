#include "Game.hpp"

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
	while (m_running)
	{
		ProcessInput();
		Update();
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
	m_gameContext.GetInputManager().Update(events);
}

void Game::Update()
{

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

	// Unbind the texture program
	m_textureProgram.Unbind();

	// Swap our buffer and draw everything to the screen!
	m_window.SwapBuffer();
}
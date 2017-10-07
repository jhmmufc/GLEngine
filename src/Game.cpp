#include "Game.hpp"

// We wish to run our game at 60fps
const ge::Timing::Time Game::TimePerFrame = ge::Timing::Seconds(1.0f / 60.0f);

Game::Game() : 
	Context(),
    Window(),
	TextureProgram(),
	Camera()
{
	// initialise our game engine
	ge::Initialise();

	// create a window
	Window.CreateWindow("Game", ScreenWidth, ScreenHeight, ge::Rendering::WindowFlags::NONE);

	// Use a black background colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Initialise our camera
	Camera.Initialise(ScreenWidth, ScreenHeight);

	// Initialise our spritebatch
	SpriteBatch.Init();

	// Load our opengl shaders
	LoadShaders();
}

void Game::LoadShaders()
{
	// Compile our texture colour shader
	TextureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	
	// Add attributes for colour, uv(texcoords) and position
	TextureProgram.AddAttribute("vertexPosition");
	TextureProgram.AddAttribute("vertexColor");
	TextureProgram.AddAttribute("vertexUV");

	// get the program ready for using by linker the shaders 
	TextureProgram.LinkShaders();
}

int Game::Run()
{
	OnInitialise();

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
	auto& inputManager = Context.GetInputManager();

	inputManager.Update(events);

	OnInput(inputManager);
}

void Game::Update(float elapsedTime)
{
	OnUpdate(elapsedTime);

	// update our camera
	Camera.Update();
}

void Game::Render()
{
	// Set the depth base to 1.0
	glClearDepth(1.0);

	// Clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind our texture program ready for rendering
	TextureProgram.Bind();

	// Activate textures and send them to the shaders
	glActiveTexture(GL_TEXTURE0);

	// Make sure the shader uses texture 0
	GLint textureUniform = TextureProgram.GetUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// Grab the camera matrix and send that to the shader
	GLint camUniform = TextureProgram.GetUniformLocation("P");
	glUniformMatrix4fv(camUniform, 1, GL_FALSE, &Camera.GetCameraMatrix()[0][0]);

	// DRAW SOME STUFF

	OnDraw();

	SpriteBatch.RenderBatches();

	// FINISH DRAWING

	// Unbind the texture program
	TextureProgram.Unbind();

	// Swap our buffer and draw everything to the screen!
	Window.SwapBuffer();
}
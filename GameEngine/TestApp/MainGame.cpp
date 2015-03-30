#include "MainGame.h"

#include <GameEngine/GameEngine.hpp>
#include <random>
#include <ctime>
#include <algorithm>

#include <SDL/SDL.h>
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

#include "Gun.h"
#include "Zombie.h"

const ge::Timing::Time MainGame::TimePerFrame = ge::Timing::Seconds(1.0f / 60.0f);

const float HUMAN_SPEED = 150.0f;
const float ZOMBIE_SPEED = 100.0f;
const float PLAYER_SPEED = 300.0f;

MainGame::MainGame()  :
    m_screenWidth(800),
    m_screenHeight(600),
    m_gameState(GameState::PLAY),
    m_fps(0),
    m_player(nullptr),
    m_numHumansKilled(0),
    m_numZombiesKilled(0) {
    // Empty
    
}

MainGame::~MainGame() {
    // Don't forget to delete the levels!
    for (size_t i = 0; i < m_levels.size(); i++) {
        delete m_levels[i];
    }
    // Don't forget to delete the humans and zombies!
	for (size_t i = 0; i < m_humans.size(); i++) {
        delete m_humans[i];
    }
	for (size_t i = 0; i < m_zombies.size(); i++) {
        delete m_zombies[i];
    }
}

void MainGame::run() {

    initSystems();

    initLevel();

    gameLoop();
}

void MainGame::initSystems() {
    // Initialize the game engine
	ge::Initialise();

    // Create our window
    m_window.CreateWindow("ZombieGame", m_screenWidth, m_screenHeight, ge::Rendering::WindowFlags::NONE);

    // Grey background color
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    // Set up the shaders
    initShaders();

    // Initialize our spritebatch
    m_agentSpriteBatch.Init();
    m_hudSpriteBatch.Init();

    // Initialize sprite font
	m_spriteFont = new ge::Rendering::SpriteFont("Fonts/chintzy.ttf", 64);

    // Set up the camera
    m_camera.Initialise(m_screenWidth, m_screenHeight);
    m_hudCamera.Initialise(m_screenWidth, m_screenHeight);
    m_hudCamera.SetPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));

    // Initialize particles
	m_bloodParticleBatch = std::make_shared<ge::Rendering::ParticleBatch2D>();

    // Initialize the particle batch and use a lambda function to define the update
    m_bloodParticleBatch->Init(1000, 2.0f,
								m_gameContext.GetResourceManager().GetTexture("Textures/particle.png"),
							   [](ge::Rendering::Particle2D& particle, float deltaTime) {
        particle.Position += particle.Velocity * deltaTime * 100.0f;
        particle.Colour.A = (GLubyte)(particle.Life * 255.0f);
    });

    m_particleEngine.AddParticleBatch(m_bloodParticleBatch);

	m_gameContext.GetAudioManager().Play2DSound("Sound/XYZ.ogg", true);
}

void MainGame::initLevel() {
    // Level 1
	m_levels.push_back(new Level("Levels/level1.txt", m_gameContext.GetResourceManager()));
    m_currentLevel = 0;

    m_player = new Player();
	auto playerTexture = m_gameContext.GetResourceManager().GetTexture("Textures/player.png");
	m_player->init(PLAYER_SPEED, m_levels[m_currentLevel]->getStartPlayerPos(), &m_gameContext.GetInputManager(), &m_camera, &m_bullets, playerTexture);

    m_humans.push_back(m_player);

    std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));

    std::uniform_int_distribution<int> randX(2, m_levels[m_currentLevel]->getWidth() - 2);
    std::uniform_int_distribution<int> randY(2, m_levels[m_currentLevel]->getHeight() - 2);

    // Add all the random humans
	auto humanTex = m_gameContext.GetResourceManager().GetTexture("Textures/human.png");
    for (int i = 0; i < m_levels[m_currentLevel]->getNumHumans(); i++) {
        m_humans.push_back(new Human);
        glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
        m_humans.back()->init(HUMAN_SPEED, pos, humanTex);
    }

    // Add the zombies
    const std::vector<glm::vec2>& zombiePositions = m_levels[m_currentLevel]->getZombieStartPositions();
	auto zombieTex = m_gameContext.GetResourceManager().GetTexture("Textures/zombie.png");
	for (size_t i = 0; i < zombiePositions.size(); i++) {
        m_zombies.push_back(new Zombie);
        m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], zombieTex);
    }

    // Set up the players guns
    const float BULLET_SPEED = 1000.0f;
	auto bulletTex = m_gameContext.GetResourceManager().GetTexture("Textures/circle.png");
	m_player->addGun(new Gun("Magnum", 10, 1, 5.0f, 30, BULLET_SPEED, bulletTex, "Sound/shots/pistol.wav", m_gameContext.GetAudioManager()));
	m_player->addGun(new Gun("Shotgun", 30, 12, 20.0f, 4, BULLET_SPEED, bulletTex, "Sound/shots/shotgun.wav", m_gameContext.GetAudioManager()));
	m_player->addGun(new Gun("MP5", 2, 1, 10.0f, 20, BULLET_SPEED, bulletTex, "Sound/shots/cg1.wav", m_gameContext.GetAudioManager()));
}

void MainGame::initShaders() {
    // Compile our color shader
    m_textureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    m_textureProgram.AddAttribute("vertexPosition");
    m_textureProgram.AddAttribute("vertexColor");
    m_textureProgram.AddAttribute("vertexUV");
    m_textureProgram.LinkShaders();
}

void MainGame::gameLoop() {
    
	ge::Timing::Clock clock;
	ge::Timing::Time timeSinceLastUpdate = ge::Timing::Time::Zero;

    // Zoom out the camera by 3x
    const float CAMERA_SCALE = 1.0f / 3.0f;
    m_camera.SetScale(CAMERA_SCALE);

    // Main loop
    while (m_gameState == GameState::PLAY) 
	{
		ge::Timing::Time elapsedTime = clock.Restart();

		timeSinceLastUpdate += elapsedTime;

        checkVictory();

        processInput();
        
        // Loop while we still have steps to process.
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

            // Update all physics here and pass in deltaTime
			updateAgents(TimePerFrame.AsSeconds());
			updateBullets(TimePerFrame.AsSeconds());
			m_particleEngine.Update(TimePerFrame.AsSeconds());
        }

        // Make sure the camera is bound to the player position
        m_camera.SetPosition(m_player->getPosition());
        m_camera.Update();
        m_hudCamera.Update();

        drawGame();
    }
}

void MainGame::updateAgents(float deltaTime) {
    // Update all humans
	for (size_t i = 0; i < m_humans.size(); i++) {
        m_humans[i]->update(m_levels[m_currentLevel]->getLevelData(),
                           m_humans,
                           m_zombies,
                           deltaTime);
    }

    // Update all zombies
	for (size_t i = 0; i < m_zombies.size(); i++) {
        m_zombies[i]->update(m_levels[m_currentLevel]->getLevelData(),
                           m_humans,
                           m_zombies,
                           deltaTime);
    }

    // Update Zombie collisions
	for (size_t i = 0; i < m_zombies.size(); i++) {
        // Collide with other zombies
		for (size_t j = i + 1; j < m_zombies.size(); j++) {
            m_zombies[i]->collideWithAgent(m_zombies[j]);
        }
        // Collide with humans
		for (size_t j = 1; j < m_humans.size(); j++) {
            if (m_zombies[i]->collideWithAgent(m_humans[j])) {
                // Add the new zombie
                m_zombies.push_back(new Zombie);
				auto zombieTex = m_gameContext.GetResourceManager().GetTexture("Textures/zombie.png");
                m_zombies.back()->init(ZOMBIE_SPEED, m_humans[j]->getPosition(), zombieTex);
                // Delete the human
                delete m_humans[j];
                m_humans[j] = m_humans.back();
                m_humans.pop_back();
            }
        }

        // Collide with player
        if (m_zombies[i]->collideWithAgent(m_player)) {
            std::cout << ("YOU LOSE") << std::endl;
        }
    }

    // Update Human collisions
	for (size_t i = 0; i < m_humans.size(); i++) {
        // Collide with other humans
		for (size_t j = i + 1; j < m_humans.size(); j++) {
            m_humans[i]->collideWithAgent(m_humans[j]);
        }
    }

    // Dont forget to update zombies
}

void MainGame::updateBullets(float deltaTime) {
    // Update and collide with world
    for (size_t i = 0; i < m_bullets.size(); ) {
        // If update returns true, the bullet collided with a wall
        if (m_bullets[i].update(m_levels[m_currentLevel]->getLevelData(), deltaTime)) {
            m_bullets[i] = m_bullets.back();
            m_bullets.pop_back();
        } else {
            i++;
        }
    }

    bool wasBulletRemoved;

    // Collide with humans and zombies
	for (size_t i = 0; i < m_bullets.size(); i++) {
        wasBulletRemoved = false;
        // Loop through zombies
		for (size_t j = 0; j < m_zombies.size();) {
            // Check collision
            if (m_bullets[i].collideWithAgent(m_zombies[j])) {
                // Add blood
                addBlood(m_bullets[i].getPosition(), 5);

                // Damage zombie, and kill it if its out of health
                if (m_zombies[j]->applyDamage(m_bullets[i].getDamage())) {
                    // If the zombie died, remove him
                    delete m_zombies[j];
                    m_zombies[j] = m_zombies.back();
                    m_zombies.pop_back();
                    m_numZombiesKilled++;
                } else {
                    j++;
                }

                // Remove the bullet
                m_bullets[i] = m_bullets.back();
                m_bullets.pop_back();
                wasBulletRemoved = true;
                i--; // Make sure we don't skip a bullet
                // Since the bullet died, no need to loop through any more zombies
                break;
            } else {
                j++;
            }
        }
        // Loop through humans
        if (wasBulletRemoved == false) {
			for (size_t j = 1; j < m_humans.size();) {
                // Check collision
                if (m_bullets[i].collideWithAgent(m_humans[j])) {
                    // Add blood
                    addBlood(m_bullets[i].getPosition(), 5);
                    // Damage human, and kill it if its out of health
                    if (m_humans[j]->applyDamage(m_bullets[i].getDamage())) {
                        // If the human died, remove him
                        delete m_humans[j];
                        m_humans[j] = m_humans.back();
                        m_humans.pop_back();
                    } else {
                        j++;
                    }

                    // Remove the bullet
                    m_bullets[i] = m_bullets.back();
                    m_bullets.pop_back();
                    m_numHumansKilled++;
                    i--; // Make sure we don't skip a bullet
                    // Since the bullet died, no need to loop through any more zombies
                    break;
                } else {
                    j++;
                }
            }
        }
    }
}

void MainGame::checkVictory() {
    // TODO: Support for multiple levels!
    // _currentLevel++; initLevel(...);

    // If all zombies are dead we win!
    if (m_zombies.empty()) {
        // Print victory message
        std::printf("*** You win! ***\n You killed %d humans and %d zombies. There are %d/%d civilians remaining",
                    m_numHumansKilled, m_numZombiesKilled, m_humans.size() - 1, m_levels[m_currentLevel]->getNumHumans());
    }
}

void MainGame::processInput() {
    SDL_Event evnt;

	std::vector<SDL_Event> events;

	// retrieve events until the function returns false
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			// If the type is quit, then quit the game
			m_gameState = GameState::EXIT;
			break;
		}

		events.push_back(evnt);
	}

	// Add all the events to the event manager
	m_gameContext.GetInputManager().Update(events);
}

void MainGame::drawGame() {
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_textureProgram.Bind();

    // Draw code goes here
    glActiveTexture(GL_TEXTURE0);

    // Make sure the shader uses texture 0
    GLint textureUniform = m_textureProgram.GetUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    glm::mat4 projectionMatrix = m_camera.GetCameraMatrix();
    GLint pUniform = m_textureProgram.GetUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Draw the level
    m_levels[m_currentLevel]->draw();

    // Begin drawing agents
    m_agentSpriteBatch.Begin();

    const glm::vec2 agentDims(AGENT_RADIUS * 2.0f);

    // Draw the humans
	for (size_t i = 0; i < m_humans.size(); i++) {
        if (m_camera.IsBoxInView(m_humans[i]->getPosition(), agentDims)) {
            m_humans[i]->draw(m_agentSpriteBatch);
        }
    }

    // Draw the zombies
	for (size_t i = 0; i < m_zombies.size(); i++) {
        if (m_camera.IsBoxInView(m_zombies[i]->getPosition(), agentDims)) {
            m_zombies[i]->draw(m_agentSpriteBatch);
        }
    }

    // Draw the bullets
	for (size_t i = 0; i < m_bullets.size(); i++) {
        m_bullets[i].draw(m_agentSpriteBatch);
    }

    // End spritebatch creation
    m_agentSpriteBatch.End();

    // Render to the screen
    m_agentSpriteBatch.RenderBatches();

    // Render the particles
    m_particleEngine.Draw(m_agentSpriteBatch);

    // Render the heads up display
    drawHud();

    // Unbind the program
	m_textureProgram.Unbind();

    // Swap our buffer and draw everything to the screen!
    m_window.SwapBuffer();
}

void MainGame::drawHud() {
    char buffer[256];
    
    glm::mat4 projectionMatrix = m_hudCamera.GetCameraMatrix();
    GLint pUniform = m_textureProgram.GetUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    m_hudSpriteBatch.Begin();

    sprintf_s(buffer, "Num Humans %d", m_humans.size());
    m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, 0),
                      glm::vec2(0.5), 0.0f, GameEngine::Rendering::ColourRGBA8(255, 255, 255, 255));

    sprintf_s(buffer, "Num Zombies %d", m_zombies.size());
    m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, 36),
                      glm::vec2(0.5), 0.0f, GameEngine::Rendering::ColourRGBA8(255, 255, 255, 255));

    m_hudSpriteBatch.End();
	m_hudSpriteBatch.RenderBatches();
}

void MainGame::addBlood(const glm::vec2& position, int numParticles) {

    static std::mt19937 randEngine(time(nullptr));
    static std::uniform_real_distribution<float> randAngle(0.0f, 360.0f);

    glm::vec2 vel(2.0f, 0.0f);
    GameEngine::Rendering::ColourRGBA8 col(255, 0, 0, 255);

    for (int i = 0; i < numParticles; i++) {
        m_bloodParticleBatch->AddParticle(position, glm::rotate(vel, randAngle(randEngine)), col, 30.0f);
    }
}
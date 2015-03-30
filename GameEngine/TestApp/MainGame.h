#pragma once

#include <GameEngine/GameEngine.hpp>

#include "Player.h"
#include "Level.h"
#include "Bullet.h"

#include <memory>

class Zombie;

enum class GameState 
{
    PLAY,
    EXIT
};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void run();

private:
    /// Initializes the core systems
    void initSystems();

    /// Initializes the level and sets up everything
    void initLevel();

    /// Initializes the shaders
    void initShaders();

    /// Main game loop for the program
    void gameLoop();

    /// Updates all agents
    void updateAgents(float deltaTime);

    /// Updates all bullets
    void updateBullets(float deltaTim);

    /// Checks the victory condition
    void checkVictory();

    /// Handles input processing
    void processInput();

    /// Renders the game
    void drawGame();

    /// Draws the HUD
    void drawHud();

    /// Adds blood to the particle engine
    void addBlood(const glm::vec2& position, int numParticles);

    /// Member Variables
	ge::Rendering::Window m_window; ///< The game window
    
	ge::Rendering::GLSLProgram m_textureProgram; ///< The shader program

	ge::Rendering::Camera m_camera; ///< Main Camera
	ge::Rendering::Camera m_hudCamera; ///< Hud Camera

	ge::Rendering::SpriteBatch m_agentSpriteBatch; ///< Draws all agents
	ge::Rendering::SpriteBatch m_hudSpriteBatch;

	ge::Rendering::ParticleEngine2D m_particleEngine;
	std::shared_ptr<ge::Rendering::ParticleBatch2D> m_bloodParticleBatch;

    std::vector<Level*> m_levels; ///< vector of all levels

    int m_screenWidth = 1024;
    int m_screenHeight = 768;

    float m_fps;

    int m_currentLevel;

    Player* m_player;
    std::vector<Human*> m_humans; ///< Vector of all humans
    std::vector<Zombie*> m_zombies; ///< Vector of all zombies
    std::vector<Bullet> m_bullets;

    int m_numHumansKilled; ///< Humans killed by player
    int m_numZombiesKilled; ///< Zombies killed by player

	ge::Rendering::SpriteFont m_spriteFont;

	ge::GameContext m_gameContext;

    GameState m_gameState;

	static const ge::Timing::Time TimePerFrame;
};


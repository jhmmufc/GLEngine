#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "AudioManager.hpp"
#include "Camera.hpp"
#include "GLSLProgram.hpp"
#include "GLTexture.hpp"
#include "ImageLoader.hpp"
#include "PicoPNG.hpp"
#include "InputManager.hpp"
#include "ResourceManager.hpp"
#include "TextureManager.hpp"
#include "Window.hpp"
#include "Vertex.hpp"
#include "Sprite.hpp"
#include "SpriteBatch.hpp"
#include "SpriteFont.hpp"
#include "ParticleBatch2D.hpp"
#include "ParticleEngine2D.hpp"
#include "Time.hpp"
#include "Clock.hpp"
#include "GameContext.hpp"

#include <SDL/SDL.h>
#include <GL/glew.h>

namespace GameEngine
{
	void Initialise();
}

namespace ge = GameEngine;

#endif
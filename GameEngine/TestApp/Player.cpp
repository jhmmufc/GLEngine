#include "Player.h"
#include <SDL/SDL.h>
#include <GameEngine/ResourceManager.hpp>

#include "Gun.h"

Player::Player() :
    _currentGunIndex(-1) {
    // Empty
}

Player::~Player() {
    // Empty
}

void Player::init(float speed, glm::vec2 pos, GameEngine::Input::InputManager* inputManager, GameEngine::Rendering::Camera* camera, std::vector<Bullet>* bullets, GameEngine::Rendering::GLTexture tex) {
    _speed = speed;
    _position = pos;
    _inputManager = inputManager;
    _bullets = bullets;
    _camera = camera;
    _color.R = 255;
    _color.G = 255;
    _color.B = 255;
    _color.A = 255;
    _health = 150;
    m_textureID = tex.ID;
}

void Player::addGun(Gun* gun) {
    // Add the gun to his inventory
    _guns.push_back(gun);

    // If no gun equipped, equip gun.
    if (_currentGunIndex == -1) {
        _currentGunIndex = 0;
    }
}

void Player::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies,
                    float deltaTime) {

	if (_inputManager->IsKeyPressed(SDLK_w)) {
        _position.y += _speed * deltaTime;
	}
	else if (_inputManager->IsKeyPressed(SDLK_s)) {
        _position.y -= _speed * deltaTime;
    }
	if (_inputManager->IsKeyPressed(SDLK_a)) {
        _position.x -= _speed * deltaTime;
	}
	else if (_inputManager->IsKeyPressed(SDLK_d)) {
        _position.x += _speed * deltaTime;
    }

	if (_inputManager->IsKeyPressed(SDLK_1) && _guns.size() >= 0) {
        _currentGunIndex = 0;
	}
	else if (_inputManager->IsKeyPressed(SDLK_2) && _guns.size() >= 1) {
        _currentGunIndex = 1;
	}
	else if (_inputManager->IsKeyPressed(SDLK_3) && _guns.size() >= 2) {
        _currentGunIndex = 2;
    }

	glm::vec2 mouseCoords = _inputManager->GetMouseCoords();
    mouseCoords = _camera->ConvertScreenToWorld(mouseCoords);


    glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);

    m_direction = glm::normalize(mouseCoords - centerPosition);

    if (_currentGunIndex != -1) {

		_guns[_currentGunIndex]->update(_inputManager->IsKeyPressed(SDL_BUTTON_LEFT),
                                        centerPosition,
                                        m_direction,
                                        *_bullets,
                                        deltaTime);
                                        

    }

    collideWithLevel(levelData);
}

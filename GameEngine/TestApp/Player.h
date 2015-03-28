#pragma once

#include "Human.h"
#include <GameEngine/InputManager.hpp>
#include <GameEngine/Camera.hpp>
#include <GameEngine/GLTexture.hpp>
#include "Bullet.h"

class Gun;

class Player : public Human
{
public:
    Player();
    ~Player();

	void init(float speed, glm::vec2 pos, GameEngine::Input::InputManager* inputManager, GameEngine::Rendering::Camera* camera, std::vector<Bullet>* bullets, GameEngine::Rendering::GLTexture tex);

    void addGun(Gun* gun);

    void update(const std::vector<std::string>& levelData,
                std::vector<Human*>& humans,
                std::vector<Zombie*>& zombies,
                float deltaTime) override;
private:
	GameEngine::Input::InputManager* _inputManager;

    std::vector<Gun*> _guns;
    int _currentGunIndex;

	GameEngine::Rendering::Camera* _camera;
    std::vector<Bullet>* _bullets;

};


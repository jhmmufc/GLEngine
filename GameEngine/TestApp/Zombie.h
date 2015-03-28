#pragma once

#include "Agent.h"
#include <GameEngine/GLTexture.hpp>

class Zombie : public Agent
{
public:
    Zombie();
    ~Zombie();

	void init(float speed, glm::vec2 pos, GameEngine::Rendering::GLTexture tex);

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombies,
                        float deltaTime) override;
private:

    Human* getNearestHuman(std::vector<Human*>& humans);
};


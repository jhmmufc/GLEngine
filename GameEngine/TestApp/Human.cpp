#include "Human.h"
#include <ctime>
#include <random>
#include <glm/gtx/rotate_vector.hpp>

Human::Human() :
    _frames(0)
{
}


Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos, GameEngine::Rendering::GLTexture tex) {

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

    _health = 20;

    _color.R = 255;
    _color.G = 255;
    _color.B = 255;
    _color.A = 255;

    _speed = speed;
    _position = pos;
    // Get random direction
    m_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
    // Make sure direction isn't zero
    if (m_direction.length() == 0) m_direction = glm::vec2(1.0f, 0.0f);

    m_direction = glm::normalize(m_direction);

	m_textureID = tex.ID;
}

void Human::update(const std::vector<std::string>& levelData,
                   std::vector<Human*>& humans,
                   std::vector<Zombie*>& zombies,
                   float deltaTime) {

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);

    _position += m_direction * _speed * deltaTime;

    // Randomly change direction every 20 frames
    if (_frames == 20) {
        m_direction = glm::rotate(m_direction, randRotate(randomEngine));
        _frames = 0;
    } else {
        _frames++;
    }

    if (collideWithLevel(levelData)) {
        m_direction = glm::rotate(m_direction, randRotate(randomEngine));
    }
}
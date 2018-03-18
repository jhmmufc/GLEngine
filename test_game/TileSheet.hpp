#pragma once

#include <GLTexture.hpp>
#include <glm/glm.hpp>

class TileSheet 
{
public:
    TileSheet(const GameEngine::Rendering::GLTexture& texture, const glm::ivec2& tileDims) :
        m_texture(texture),
        m_dims(tileDims)
    {

    }

    auto GetUVs(int index) const
    {
        const int xTile = index % m_dims.x;
        const int yTile = index / m_dims.x;

        glm::vec4 uvs;
        uvs.x = xTile / static_cast<float>(m_dims.x);
        uvs.y = yTile / static_cast<float>(m_dims.y);
        uvs.z = 1.0f / m_dims.x;
        uvs.w = 1.0f / m_dims.y;

        return uvs;
    }

    auto Id() const
    {
        return m_texture.ID;
    }

private:
    GameEngine::Rendering::GLTexture m_texture;
    glm::ivec2 m_dims;
};

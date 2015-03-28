#include "Level.h"

#include <fstream>
#include <iostream>

Level::Level(const std::string& fileName, GameEngine::ResourceManagement::ResourceManager& resourceManager) {

    std::ifstream file;
    file.open(fileName);

    // Throw away the first string in tmp
    std::string tmp;

    file >> tmp >> _numHumans;

    std::getline(file, tmp); // Throw away the rest of the first line

    // Read the level data
    while (std::getline(file, tmp)) {
        _levelData.emplace_back(tmp);
    }    
    
    _spriteBatch.init();
    _spriteBatch.begin();

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    GameEngine::Rendering::ColourRGBA8 whiteColor;
    whiteColor.R = 255;
    whiteColor.G = 255;
    whiteColor.B = 255;
    whiteColor.A = 255;

    // Render all the tiles
    for (int y = 0; y < _levelData.size(); y++) {
        for (int x = 0; x < _levelData[y].size(); x++) {
            // Grab the tile
            char tile = _levelData[y][x];

            // Get dest rect
            glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

            // Process the tile
            switch (tile) {
                case 'B':
                case 'R':
                    _spriteBatch.draw(destRect,
                                      uvRect,
									  resourceManager.GetTexture("Textures/red_bricks.png").ID,
                                      0.0f,
                                      whiteColor);      
                    break;
                case 'G':
                    _spriteBatch.draw(destRect,
                                      uvRect,
									  resourceManager.GetTexture("Textures/glass.png").ID,
                                      0.0f,
                                      whiteColor);
                    break;
                case 'L':
                    _spriteBatch.draw(destRect,
                                      uvRect,
									  resourceManager.GetTexture("Textures/light_bricks.png").ID,
                                      0.0f,
                                      whiteColor);
                    break;
                case '@':
                    _levelData[y][x] = '.'; /// So we dont collide with a @
                    _startPlayerPos.x = x * TILE_WIDTH;
                    _startPlayerPos.y = y * TILE_WIDTH;
                    break;
                case 'Z':
                    _levelData[y][x] = '.'; /// So we dont collide with a Z
                    _zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
                    break;
                case '.':
                    break;
                default:
                    std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
                    break;
            }
        }
    }

    _spriteBatch.end();

}


Level::~Level()
{
}


void Level::draw() {
    _spriteBatch.renderBatch();
}
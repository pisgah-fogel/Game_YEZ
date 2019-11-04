#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "RessourcesManager.hpp"
#include "Log.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @param texid Texture id (registered in the ressourceManager)
	 * @param tiles array of Rect id (registered in the ressource Manager)
	 * @param tileSize size (pixel) of one tile
	 * @param width number of tiles per line
	 * @param height number of tiles per row
	 */
	TileMap(unsigned int texid, const unsigned int* tiles, sf::Vector2u tileSize, unsigned int width, unsigned int height): m_tileset(nullptr)
	{
		m_tileset = core::RessourcesManager::getInstance()->getTexture(texid);
		if (!m_tileset) {
			LOG("Error cannot get texture, abord");
		}

		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		for (unsigned int i = 0; i<width; i++) {
			for (unsigned int j = 0; j<height; j++) {
				// Vertex's Quad position
				sf::Vertex* quad = &m_vertices[(i+j*width)*4];
				quad[0].position = sf::Vector2f(i*tileSize.x, j*tileSize.y);
				quad[1].position = sf::Vector2f((i+1)*tileSize.x, j*tileSize.y);
				quad[2].position = sf::Vector2f((i+1)*tileSize.x, (j+1)*tileSize.y);
				quad[3].position = sf::Vector2f(i*tileSize.x, (j+1)*tileSize.y);

				// Mapping on the texture
				unsigned int rectid = tiles[i+j*width];
				sf::IntRect* rect = core::RessourcesManager::getInstance()->getRect(rectid);
				if (rect) {
					quad[0].texCoords = sf::Vector2f(rect->left, rect->top);
					quad[1].texCoords = sf::Vector2f(rect->left+rect->width, rect->top);
					quad[2].texCoords = sf::Vector2f(rect->left+rect->width, rect->top+rect->height);
					quad[3].texCoords = sf::Vector2f(rect->left, rect->top+rect->height);
				}
			}
		}
	}
	~TileMap()
	{
		LOG("Debug TileMap is freed");
	}

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = m_tileset;
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture* m_tileset;
};

#endif // TILEMAP_HPP

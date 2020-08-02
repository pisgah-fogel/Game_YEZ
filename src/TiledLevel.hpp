#ifndef TILEDLEVEL_HPP
#define TILEDLEVEL_HPP

#include <SFML/Graphics.hpp>
#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "TileMap.hpp"

class TiledLevel: public sf::Drawable, public sf::Transformable
{
	public:
		TiledLevel() {
		objectsMap = new TileMap(0, testLevel_objects, sf::Vector2u(16, 16), 6, 6);
		}

		~TiledLevel() {
			delete (objectsMap);
			LOG("Ok TiledLevel freed");
		}

		unsigned int getSpriteAt(size_t x, size_t y) {
			return testLevel_objects[x + y*6];
		}

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			target.draw(*objectsMap, states);
		}

	private:
		TileMap* objectsMap;

		unsigned int testLevel_objects[36] =
		{
			33, 33, 33, 33, 33, 33,
			33, 33, 33, 33, 33, 33,
			33, 33, 34, 32, 33, 33,
			33, 33, 33, 33, 33, 33,
			32, 33, 33, 33, 33, 33,
			33, 33, 33, 33, 33, 33,
		};
};

#endif // TILEDLEVEL_HPP

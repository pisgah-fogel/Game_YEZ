#ifndef ANIMSPRITE_HPP
#define ANIMSPRITE_HPP

#include <SFML/Graphics.hpp>
#include "RessourcesManager.hpp"
#include "Log.hpp"

class AnimSprite: public sf::Drawable, public sf::Transformable
{
public:
	AnimSprite(unsigned int id) {
		refreshrate = 0.5f;
		u_loop_a = u_loop_b = u_current = 0;
		u_rects = core::RessourcesManager::getInstance()->getRectSet(id);
		sf::Texture* tex = core::RessourcesManager::getInstance()->getTexture(id/100);
		if (u_rects == nullptr || tex == nullptr) {
			LOG("Error can't found texture");
			u_visible = false;
		}
		u_sprite = new sf::Sprite();
		u_sprite->setTexture(*tex);
		u_it = u_rects->begin();
		u_sprite->setTextureRect(*u_it);
		u_visible = true;
		u_reverse = false;
	}
	~AnimSprite() {
		if(u_sprite != nullptr)
			delete(u_sprite);
	}
	void next() {
		if (u_sprite == nullptr || u_rects == nullptr)
			return;
		
		u_sprite->setTextureRect(*u_it);
		if (u_it == u_rects->end())
			u_it = u_rects->begin();
		u_it++;
	}
	void loop(size_t a, size_t b, float dt) {
		if (a > b) {
			LOG("Error a > b");
			a = b = 0;
		}
		refreshrate = dt;
		u_loop_a = a;
		u_current = a;
		u_loop_b = b;
	}
	void rloop(size_t a, size_t b, float dt) {
		u_reverse = true;
		loop(a, b, dt);
	}
	void update(sf::Time &dt) {
		u_usec += dt.asSeconds();
		if (u_usec > refreshrate) {
			u_usec = 0.f;

			u_sprite->setTextureRect((*u_rects)[u_current]);

			if (u_reverse) {
				if (u_current == u_loop_a)
					u_current = u_loop_b;
				else
					u_current --;
			}
			else {
				if (u_current == u_loop_b || u_current >= u_rects->size())
					u_current = u_loop_a;
				else
					u_current ++;
			}
		}
	}
	
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (u_visible) {
			states.transform *= getTransform();
			target.draw(*u_sprite, states);
		}
	}
	bool u_visible;
	bool u_reverse;
	sf::Sprite* u_sprite;
	std::vector<sf::IntRect>::iterator u_it;
	std::vector<sf::IntRect>* u_rects;
	float u_usec, refreshrate;
	size_t u_loop_a, u_loop_b, u_current;
	
};

#endif // ANIMSPRITE_HPP

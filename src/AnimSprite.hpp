#ifndef ANIMSPRITE_HPP
#define ANIMSPRITE_HPP

#include <SFML/Graphics.hpp>
#include "RessourcesManager.hpp"

class AnimSprite: public sf::Drawable, public sf::Transformable
{
public:
	AnimSprite(unsigned int id) {
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
	}
	~AnimSprite() {
		if(u_sprite != nullptr)
			delete(u_sprite);
	}
	void next() {
		if (u_sprite == nullptr || u_rects == nullptr)
			return;
		u_it++;
		if (u_it == u_rects->end())
			u_it = u_rects->begin();
		u_sprite->setTextureRect(*u_it);
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
	sf::Sprite* u_sprite;
	std::vector<sf::IntRect>::iterator u_it;
	std::vector<sf::IntRect>* u_rects;
	
};

#endif // ANIMSPRITE_HPP

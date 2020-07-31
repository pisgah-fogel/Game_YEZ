#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "RessourcesManager.hpp"
#include "Log.hpp"

class Character: public sf::Drawable, public sf::Transformable
{
public:
	Character(unsigned int id) {
        refreshrate = 0.5f;
        u_rects = core::RessourcesManager::getInstance()->getRectSet(id);
		sf::Texture* tex = core::RessourcesManager::getInstance()->getTexture(id/100);
		if (u_rects == nullptr || tex == nullptr) {
			LOG("Error can't found texture");
			u_visible = false;
		}
		u_sprite = new sf::Sprite();
		u_sprite->setTexture(*tex);
		u_sprite->setTextureRect(*u_rects->begin());
		u_visible = true;
        stopped = true;
    }

    ~Character() {
        if(u_sprite != nullptr)
			delete(u_sprite);
    }

    void update(sf::Time &dt) {
		u_usec += dt.asSeconds();
		if (!stopped && u_usec > refreshrate) {
			u_usec = 0.f;
            LOG("Debug Character anim %d", *current_anim_vector_it);
			u_sprite->setTextureRect((*u_rects)[*current_anim_vector_it]);
            current_anim_vector_it ++;
            if (current_anim_vector_it == current_anim_vector.end())
                current_anim_vector_it = current_anim_vector.begin();
		}
	}

    // Finish the animation the stop
    void stop_anim() {
        LOG("Debug TODO");
        current_anim_vector_it = current_anim_vector.begin(); // TODO check than the animation stop correctly
        u_sprite->setTextureRect((*u_rects)[*current_anim_vector_it]);
        stopped = true;
    }

    void play_anim(std::string anim_name) {
        LOG("Debug TODO");
        if (animations.find(anim_name) != animations.end()) {
            current_anim_vector = animations[anim_name];
            current_anim_vector_it = current_anim_vector.begin();
            stopped = false;
        } else {
            LOG("Error Animation %s does not exist", anim_name.c_str());
            return;
        }
    }

    void register_anim(std::string anim_name, std::vector<size_t> anim) {
        LOG("Debug TODO");
        animations[anim_name] = anim;
        current_anim_vector = anim;
        current_anim_vector_it = anim.begin();
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
    std::map<std::string, std::vector<size_t>> animations;
    std::vector<size_t> current_anim_vector;
    std::vector<size_t>::iterator current_anim_vector_it;

	std::vector<sf::IntRect>* u_rects;
	float u_usec, refreshrate;
    bool stopped = true;
};

#endif // CHARACTER_HPP
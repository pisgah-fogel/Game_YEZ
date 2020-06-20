#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
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
		u_it = u_rects->begin();
		u_sprite->setTextureRect(*u_it);
		u_visible = true;
        stopped = true;

        front_start = 0;
        front_end = 0;
        right_start = 0;
        right_end = 0;
        back_start = 0;
        back_end = 0;
        u_current = 0;
        u_loop_a = 0;
        u_loop_b = 0;
    }

    ~Character() {
        if(u_sprite != nullptr)
			delete(u_sprite);
    }

    void set_forward_anim(size_t start, size_t end) {
        if (end > start && end < u_rects->size()) {
            front_start = start;
            front_end = end;
        } else {
            LOG("Error can't create anim, index out of range");
        }
    }

    void set_backward_anim(size_t start, size_t end) {
        if (end > start && end < u_rects->size()) {
            back_start = start;
            back_end = end;
        } else {
            LOG("Error can't create anim, index out of range");
        }
    }

    void set_right_anim(size_t start, size_t end) {
        if (end > start && end < u_rects->size()) {
            right_start = start;
            right_end = end;
        } else {
            LOG("Error can't create anim, index out of range");
        }
    }

    void update(sf::Time &dt) {
		u_usec += dt.asSeconds();
		if (!stopped && u_usec > refreshrate) {
			u_usec = 0.f;

			u_sprite->setTextureRect((*u_rects)[u_current]);

            if (u_current == u_loop_b)
                u_current = u_loop_a;
            else
                u_current ++;
		}
	}

    // Finish the animation the stop
    void anim_stop() {
        u_sprite->setTextureRect((*u_rects)[u_loop_b]); // TODO check than the animation stop correctly

        u_loop_a = 0;
        u_loop_b = 0;
        stopped = true;
    }

    void anim_forward() {
        u_loop_a = front_start;
        u_loop_b = front_end;
        stopped = false;
    }

    void anim_backward() {
        u_loop_a = back_start;
        u_loop_b = back_end;
        stopped = false;
    }

    void anim_left() {
        u_loop_a = right_start;
        u_loop_b = right_end;
        stopped = false;
    }

    void anim_right() {
        u_loop_a = right_start;
        u_loop_b = right_end;
        stopped = false;
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
	float u_usec, refreshrate;
    bool stopped = true;
    size_t front_start, front_end;
    size_t right_start, right_end;
    size_t back_start, back_end;
    size_t u_current;
    size_t u_loop_a, u_loop_b;
};

#endif // CHARACTER_HPP
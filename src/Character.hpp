#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "RessourcesManager.hpp"
#include "Log.hpp"
#include <cmath>

class Character: public sf::Drawable, public sf::Transformable
{
	public:
		Character(unsigned int id) {
			refreshrate = 0.1f;
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
			needToMove = false;
		}

		~Character() {
			if(u_sprite != nullptr)
				delete(u_sprite);
		}

		void update(sf::Time &dt) {
			u_usec += dt.asSeconds();
			if (!stopped && u_usec > refreshrate) {
				u_usec = 0.f;
				u_sprite->setTextureRect((*u_rects)[*current_anim_vector_it]);
				current_anim_vector_it ++;
				if (current_anim_vector_it == current_anim_vector.end())
					current_anim_vector_it = current_anim_vector.begin();
				if(needToMove) {
					float sec = dt.asSeconds();
					sf::Vector2f t = sf::Vector2f(tile_target_diff.x*260*sec,tile_target_diff.y*260*sec);
					this->move(t);
					if (abs(this->getPosition().x - target_position.x) < 1.f && abs(this->getPosition().y - target_position.y) < 1.f) {
						LOG("Test In TILE %f %f, -> %f %f",this->getPosition().x, this->getPosition().y, target_position.x, target_position.y);
						tile_position = tile_target_position;
						needToMove = false;
						stopped = true;
					}
				}
			}
		}

		bool isMoving() {
			return needToMove;
		}

		// Finish the animation the stop
		void stop_anim() {
			if (!stopped) {
				current_anim_vector_it = current_anim_vector.begin(); // TODO check than the animation stop correctly
				u_sprite->setTextureRect((*u_rects)[*current_anim_vector_it]);
				stopped = true;
			}
		}

		sf::FloatRect get_collision() {
			sf::FloatRect x;
			x.left = this->getPosition().x + 5;
			x.top = this->getPosition().y + 3;
			x.width = 16 - 5;
			x.height = 16 - 3;
			return x;
		}

		void play_anim(std::string anim_name) {
			// We need to update the animation if it was stopped or if it has changed
			if (!stopped && current_anim_name == anim_name)
				return;
			else if (animations.find(anim_name) != animations.end()) {
				current_anim_name = anim_name;
				current_anim_vector = animations[anim_name];
				current_anim_vector_it = current_anim_vector.begin();
				stopped = false;
			} else {
				LOG("Error Animation %s does not exist", anim_name.c_str());
				return;
			}
		}

		void static_anim(size_t anim) {
			if (anim >= u_rects->size()) {
				LOG("Error Index %d is out of range (%d)", anim, u_rects->size());
				return;
			}
			stopped = true;
			u_sprite->setTextureRect((*u_rects)[anim]);
		}

		void register_anim(std::string anim_name, std::vector<size_t> anim) {
			current_anim_name = anim_name;
			animations[anim_name] = anim;
			current_anim_vector = anim;
			current_anim_vector_it = anim.begin();
		}

		void set_tile_position(sf::Vector2i vec) {
			tile_position = vec;
			target_position = tilePositionToPixelPosition(tile_position);
			this->setPosition(target_position);
			tile_target_diff = sf::Vector2i(0, 0);
			needToMove = false;
		}

		void move_tile(sf::Vector2i vec) {
			tile_target_diff = vec;
			tile_target_position = vec + tile_position;
			target_position = tilePositionToPixelPosition(tile_target_position);
			needToMove = true;
			stopped = true;
		}

		sf::Vector2f tilePositionToPixelPosition(sf::Vector2i vec) {
			return sf::Vector2f(vec.x*16.f, vec.y*16.f);
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
		std::string current_anim_name;
		std::vector<size_t>::iterator current_anim_vector_it;

		sf::Vector2i tile_position;
		sf::Vector2i tile_target_diff;
		sf::Vector2i tile_target_position;
		bool needToMove;
		sf::Vector2f target_position;

		std::vector<sf::IntRect>* u_rects;
		float u_usec, refreshrate;
		bool stopped = true;
};

#endif // CHARACTER_HPP

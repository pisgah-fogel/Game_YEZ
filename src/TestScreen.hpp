#ifndef TESTSCREEN_HPP
#define TESTSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Screen.hpp"
#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "Config.hpp"
#include "TileMap.hpp"
#include "Particles.hpp"

namespace gui
{
	class TestScreen: Screen
	{
	public:
		TestScreen(): shape(5.f)
		{
		}
		~TestScreen()
		{
			if (testAnim)
				delete (testAnim);
			if (userView)
				delete (userView);
			if (tileMap)
				delete (tileMap);
			if (particles)
				delete (particles);
			LOG("Debug Test screen freed");
		}
		virtual void init(sf::RenderWindow& win)
		{
			defaultView = &win.getDefaultView(); // is sf::View(0, 0, 1000, 1000)
			userView = new sf::View(sf:: FloatRect(0, 0, 2000, 2000));
			core::RessourcesManager::getInstance()->parseFile("test.conf");
			core::RessourcesManager::getInstance()->loadDefaultFont();

			text.setFont(*core::RessourcesManager::getInstance()->getDefaultFont());
			text.setString("This is a test");

			const unsigned int testLevel[] =
			{
				7, 1, 0, 1, 0, 7,
				0, 1, 3, 3, 0, 1,
				0, 9, 9, 9, 9, 1,
				0, 1, 4, 4, 0, 1,
				0, 1, 5, 5, 0, 1,
				7, 1, 0, 1, 0, 7,
			};
			tileMap = new TileMap(0, testLevel, sf::Vector2u(50, 50), 6, 6);

			testAnim = new AnimSprite(100);
			testAnim->rloop(0, 3, 0.5f);
			shape.setFillColor(sf::Color::Green);

			particles = new ParticleSystem(0,10);
			particles->setEmitter(sf::Vector2f(50.f,50.f));

			//std::string path = utils::Config::getInstance()->getString("tileset");
			//core::RessourcesManager::getInstance()->loadTexture(path,0);
			//sf::Texture *tex = core::RessourcesManager::getInstance()->getTexture(0);
			sprite1 = core::RessourcesManager::getInstance()->createSprite(0);
			sprite2 = core::RessourcesManager::getInstance()->createSprite(1);
			sprite3 = core::RessourcesManager::getInstance()->createSprite(2);
			sprite4 = core::RessourcesManager::getInstance()->createSprite(3);

			sprite1->setPosition(sf::Vector2f(10.f, 50.f));
			sprite2->setPosition(sf::Vector2f(60.f, 50.f));
			sprite3->setPosition(sf::Vector2f(120.f, 50.f));
			sprite4->setPosition(sf::Vector2f(60.f, 110.f));
			//sprite1->move(sf::Vector2f(5.f, 10.f));
			//sprite1->setOrigin(sf::Vector2f(25.f, 25.f));
			//sf::Vector2f position = sprite1.getPosition();
		}
		virtual void preCompute(sf::Time &dt)
		{
			testAnim->update(dt);
			particles->update(dt);
		}
		virtual bool handleEvent(sf::Event& event)
		{
            if (event.type == sf::Event::Closed)
				return false; // exit
			else if (event.type == sf::Event::MouseButtonPressed)
				testAnim->next();
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					return false; // exit
				} else if (event.key.code == sf::Keyboard::Z) {
					sprite1->move(sf::Vector2f(0.f, -2.f));
				} else if (event.key.code == sf::Keyboard::S) {
					sprite1->move(sf::Vector2f(0.f, 2.f));
				} else if (event.key.code == sf::Keyboard::Q) {
					sprite1->move(sf::Vector2f(-2.f, 0.f));
				} else if (event.key.code == sf::Keyboard::D) {
					sprite1->move(sf::Vector2f(2.f, 0.f));
				}
			}
			return true;
		}
		virtual void draw(sf::RenderWindow& win)
		{
			win.clear();
			win.setView(*defaultView);
			if (tileMap)
				win.draw(*tileMap);
			win.draw(shape);
			win.draw(text);
			win.draw(*sprite2);
			win.draw(*sprite3);
			win.draw(*sprite4);
			win.setView(*userView);
			win.draw(*sprite1);
			win.draw(*testAnim);
			win.draw(*particles);
			win.display();
		}
		virtual void postCompute()
		{
		}

		sf::CircleShape shape;
		sf::Sprite* sprite1;
		sf::Sprite* sprite2;
		sf::Sprite* sprite3;
		sf::Sprite* sprite4;
		AnimSprite* testAnim;
		const sf::View* defaultView;
		sf::View* userView;
		sf::Text text;
		TileMap* tileMap;
		ParticleSystem *particles;
	};
}

#endif // TESTSCREEN_HPP

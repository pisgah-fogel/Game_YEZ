#ifndef TESTSCREEN_HPP
#define TESTSCREEN_HPP


#include <SFML/Graphics.hpp>
#include <memory>

#include "Screen.hpp"
#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "Config.hpp"

namespace gui
{
	class TestScreen: Screen
	{
	public:
		TestScreen(): shape(100.f)
		{
		}
		~TestScreen()
		{
			LOG("Debug Test screen freed");
		}
		virtual void init()
		{
			core::RessourcesManager::getInstance()->parseFile("test.conf");
			core::RessourcesManager::getInstance()->loadDefaultFont();

			sf::Text text;
			text.setFont(*core::RessourcesManager::getInstance()->getDefaultFont());
			text.setString("Hello world");

			shape.setFillColor(sf::Color::Green);

			//std::string path = utils::Config::getInstance()->getString("tileset");
			//core::RessourcesManager::getInstance()->loadTexture(path,0);
			//sf::Texture *tex = core::RessourcesManager::getInstance()->getTexture(0);
			//sf::Sprite* sprite = core::RessourcesManager::getInstance()->createSprite(1);
			//sf::Sprite* sprite2 = core::RessourcesManager::getInstance()->createSprite(0);
			//sf::Sprite* sprite3 = core::RessourcesManager::getInstance()->createSprite(2);

			//AnimSprite testAnim(3);
			//sprite->setPosition(sf::Vector2f(10.f, 50.f));
			//sprite2->setPosition(sf::Vector2f(60.f, 50.f));
			//sprite3->setPosition(sf::Vector2f(120.f, 50.f));
			//sprite->move(sf::Vector2f(5.f, 10.f));
			//sprite->setOrigin(sf::Vector2f(25.f, 25.f));
			//sf::Vector2f position = sprite.getPosition();
		}
		virtual void preCompute()
		{
		}
		virtual bool handleEvent(sf::Event& event)
		{
            if (event.type == sf::Event::Closed)
				return false; // exit
			//else if (event.type == sf::Event::MouseButtonPressed)
			//	testAnim.next();
			return true;
		}
		virtual void draw(sf::RenderWindow& win)
		{
			win.clear();
			win.draw(shape);
			//win.draw(text);
			win.display();
		}
		virtual void postCompute()
		{
		}

		sf::CircleShape shape;
	};
}

#endif // TESTSCREEN_HPP

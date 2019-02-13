#include <SFML/Graphics.hpp>
#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "Config.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	core::RessourcesManager::getInstance()->loadDefaultFont();

	sf::Text text;
	text.setFont(*core::RessourcesManager::getInstance()->getDefaultFont());
	text.setString("Hello world");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	sf::Texture texture;
	std::string path = utils::Config::getInstance()->getString("tileset");
	if (!texture.loadFromFile(path))
	{
		LOG("Error can't load texture");
	}
	texture.setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	sprite.setPosition(sf::Vector2f(10.f, 50.f));
	sprite.move(sf::Vector2f(5.f, 10.f));
	sprite.setOrigin(sf::Vector2f(25.f, 25.f));
	sf::Vector2f position = sprite.getPosition();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
		window.draw(text);
		window.draw(sprite);
        window.display();
    }

    return 0;
}

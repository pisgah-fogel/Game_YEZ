#include <SFML/Graphics.hpp>
#include "RessourcesManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	core::RessourcesManager::getInstance()->loadDefaultFont();
	sf::Text text;
	text.setFont(*core::RessourcesManager::getInstance()->getDefaultFont());
	text.setString("Hello world");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

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
        window.display();
    }

    return 0;
}

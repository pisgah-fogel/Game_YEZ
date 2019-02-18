#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "Config.hpp"
#include "Screen.hpp"
#include "TestScreen.hpp"

/*!
 * \file ScreenManager.hpp
 * \brief gère l'affichage de plusieurs écrans
 * \author Aubin Detrez
 * \version 0.1
 */

namespace gui
{
	/*!
	 * TODO
	 */
	class ScreenManager
	{
	public:
		ScreenManager(): u_window(sf::VideoMode(800, 600), "Game YEZ")
		{
			u_screen = (Screen*)new TestScreen();
			u_screen->init();
		}
		int mainLoop()
		{
			while(u_window.isOpen())
			{
				sf::Event event;
				while (u_window.pollEvent(event))
					if(!u_screen->handleEvent(event))
						u_window.close();
				u_screen->preCompute();
				u_screen->draw(u_window);
				u_screen->postCompute();
			}
			return 0;
		}
		~ScreenManager()
		{
			delete (u_screen);
		}
	private:
		sf::RenderWindow u_window;
		gui::Screen* u_screen;
		
	};
}
#endif // SCREENMANAGER_HPP

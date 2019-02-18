#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "Config.hpp"

namespace gui
{
	class Screen
	{
	public:
		Screen(){};
		virtual ~Screen(){};
		virtual void init()=0;
		virtual void preCompute()=0;
		virtual bool handleEvent(sf::Event& event)=0;
		virtual void draw(sf::RenderWindow& win)=0;
		virtual void postCompute()=0;
	};
}

#endif // SCREEN_HPP

#include "RessourcesManager.hpp"
#include "Log.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

bool core::RessourcesManager::loadDefaultFont()
{
	if (!u_font.loadFromFile("data/Roboto-Bold.ttf")) {
			LOG("Error Can't load font");
		return false;
	}
	LOG("Ok font loaded");
	return true;
}

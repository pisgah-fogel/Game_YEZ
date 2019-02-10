#include "RessourcesManager.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

bool core::RessourcesManager::loadDefaultFont()
{
	if (!u_font.loadFromFile("data/Roboto-Bold.ttf")) {
			std::cout<<"[x] RessourcesManager::loadDefaultFont Can't load font"<<std::endl;
		return false;
	}
	std::cout<<"[v] RessourcesManager::loadDefaultFont Font loaded"<<std::endl;
	return true;
}

#include "RessourcesManager.hpp"
#include "Log.hpp"

#include <SFML/Graphics.hpp>

#include "Config.hpp"

bool core::RessourcesManager::loadDefaultFont()
{
	if (!utils::Config::getInstance()->stringExist("default_font")) {
		LOG("Error No \"default_font\" configuration found");
		return false;
	}
	if (!u_font.loadFromFile(utils::Config::getInstance()->getString("default_font"))) {
		LOG("Error Can't load font");
		return false;
	}
	LOG("Ok font loaded");
	return true;
}

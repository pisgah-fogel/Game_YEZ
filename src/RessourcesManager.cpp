#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "Config.hpp"

#include <SFML/Graphics.hpp>
#include <fstream>


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

/*
 * Config file example:
 * f <file id> <texture filename> # open texture file
 * t <texture id> x y w h # texture coordinate
 * ts <texture set id> <size>
 * s x y w h
 * s x y w h
 * ...
 */
bool core::RessourcesManager::parseFile(const std::string& filename)
{
	size_t i = 0;
	std::string a, b;
	std::ifstream ifs;
	ifs.open (filename, std::ifstream::in);
	int x, y, w, h;
	unsigned int id;
	unsigned int size;
	unsigned int current_file;
	unsigned int current_texset;
	bool ts_set = false; // current_texset is set
	bool file_set = false; // current_file is set

	while (ifs.good()) {
		std::getline(ifs, a, ' ');
		if (a == "f") {
			ts_set = false;
			file_set = true;
			std::getline(ifs, b, ' ');
			current_file = std::stoi(b);
			std::getline(ifs, b);
			LOG("Debug id: %d",id);
			LOG("Debug filename: \"%s\"", b.c_str());
			loadTexture(b, current_file);
		} else if (a == "t") {
			ts_set = false;
			if (!file_set) {
				LOG("Error %s, line %s, no file loaded", filename.c_str(), i+1);
				continue;
			}

			std::getline(ifs, b, ' ');
			id = std::stoi(b);

			std::getline(ifs, b, ' ');
			x = std::stoi(b);

			std::getline(ifs, b, ' ');
			y = std::stoi(b);

			std::getline(ifs, b, ' ');
			w = std::stoi(b);

			std::getline(ifs, b);
			h = std::stoi(b);
			LOG("Texture %d, %d-%d-%d-%d", id, x, y, w, h);
			u_rects[current_file*100 + id] = sf::IntRect(x, y, w, h);
			
		} else if (a == "ts") {
			if (!file_set) {
				LOG("Error %s, line %s, no file loaded", filename.c_str(), i+1);
				continue;
			}

			ts_set = true;
			std::getline(ifs, b, ' ');
			current_texset = std::stoi(b);

			std::getline(ifs, b);
			size = std::stoi(b);
			LOG("TextureSet, id %d size %d", id, size);
		} else if (a == "s") {
			if (!ts_set) {
				LOG("Error %s, line %s, no previous texture set", filename.c_str(), i+1);
				continue;
			}

			std::getline(ifs, b, ' ');
			x = std::stoi(b);

			std::getline(ifs, b, ' ');
			y = std::stoi(b);

			std::getline(ifs, b, ' ');
			w = std::stoi(b);

			std::getline(ifs, b);
			h = std::stoi(b);
			LOG("Anim %d-%d-%d-%d", x, y, w, h);
		} else {
			LOG("Error unreconnised command %s", a.c_str());
		}
		i++;
	}
	LOG("Ok read %d lines from %s", i, filename.c_str());

	ifs.close();
}

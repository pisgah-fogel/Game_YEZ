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
	size_t count_ts=0;
	bool ts_set = false; // current_texset is set
	bool file_set = false; // current_file is set
	std::vector<sf::IntRect> current_ts_vec;

	LOG("Start parsing %s", filename.c_str());
	while (ifs.good()) {
		a.clear();
		ifs>>a;
		if (a == "#") {
			std::string comment_line;
			std::getline(ifs, comment_line);
			LOG("Test Comment: %s", comment_line.c_str());
		}
		else if (a == "f") {
			if(ts_set) {
				LOG("Error please finish the texture set before opening an other file");
				return false;
			}
			file_set = true;
			ifs>>current_file;
			ifs>>b;
			LOG("Filename: \"%s\", id: %d", b.c_str(), id);
			loadTexture(b, current_file);
		} else if (a == "t") {
			if(ts_set) {
				LOG("Error please finish the texture set");
				return false;
			}
			if (!file_set) {
				LOG("Error %s, line %s, no file loaded", filename.c_str(), i+1);
				return false;
			}
			ifs>>id;
			ifs>>x;
			ifs>>y;
			ifs>>w;
			ifs>>h;
			LOG("\tTexture %d, %d-%d-%d-%d", id, x, y, w, h);
			u_rects[current_file*100 + id] = sf::IntRect(x, y, w, h);
		} else if (a == "ts") {
			if(ts_set) {
				LOG("Error please complite the texture set before creating an other one");
				return false;
			}
			if (!file_set) {
				LOG("Error %s, line %d, no file loaded", filename.c_str(), i+1);
				return false;
			}
			ts_set = true;
			ifs>>current_texset;
			ifs>>size;
			current_ts_vec.clear();
			count_ts=0;
			LOG("\tTextureSet, id %d size %d", id, size);
		} else if (a == "s") {
			if (!ts_set) {
				LOG("Error %s, line %d, no previous texture set", filename.c_str(), i+1);
				return false;
			}
			ifs>>x;
			ifs>>y;
			ifs>>w;
			ifs>>h;
			count_ts++;
			LOG("\t\tAnim %d-%d-%d-%d", x, y, w, h);
			if(count_ts>size) {
				LOG("Error too many coordinates for texture set");
				return false;
			}
			else if(count_ts==size) {
				current_ts_vec.push_back(sf::IntRect(x, y, w, h));
				u_anims[current_file*100 + current_texset] = current_ts_vec;
				ts_set = false;
				count_ts = 0;
				LOG("\tAnim %d registered", current_texset);
			}
			else {
				current_ts_vec.push_back(sf::IntRect(x, y, w, h));
			}
		} else {
			LOG("\tWarning ignoring command \"%s\" line %d", a.c_str(), i);
		}
		i++;
	}
	LOG("Ok read %d lines from %s", i, filename.c_str());

	ifs.close();
	return true; // everythings works
}

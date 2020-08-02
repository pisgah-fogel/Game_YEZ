#ifndef TILEDLEVEL_HPP
#define TILEDLEVEL_HPP

#include <SFML/Graphics.hpp>
#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "TileMap.hpp"
#include <fstream>
#include <ctime>

typedef struct {
	unsigned int tile_sprite_id;
	unsigned int object_sprite_id;
	bool collision;
	unsigned int chest_id; // 0 for no chest

	unsigned int distributor_id; // a place containing fishes or a tree is a distributor

	unsigned int dps; // damage per second

	unsigned int door_destination;// à for no door
} Object;

std::string getTimeString() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
	return std::string(buffer);
}

void init_object(Object* obj) {
	obj->tile_sprite_id = 0;
	obj->object_sprite_id = 0;
	obj->collision = false;
	obj->chest_id = 0;
	obj->distributor_id = 0;
	obj->dps = 0;
	obj->door_destination = 0;
}

void loadLevelFromFile(const std::string& filename, std::vector<Object>* levelVector) {
	unsigned int item_count = 0;
	unsigned int object_count = 0;
	std::ifstream ifs;
	std::string a;
	ifs.open (filename, std::ifstream::in);
	while (ifs.good()) {
		a.clear();
		ifs>>a;
		if (a == "#") {
			std::string comment_line;
			std::getline(ifs, comment_line);
			LOG("Test Comment: %s", comment_line.c_str());
		} else if (a == "i") {
			Object obj;
			ifs >> obj.tile_sprite_id;
			ifs >> obj.object_sprite_id;
			ifs >> obj.collision;
			ifs >> obj.chest_id;
			ifs >> obj.distributor_id;
			ifs >> obj.dps;
			ifs >> obj.door_destination;
			levelVector->push_back(obj);
			object_count++;
		}
		else {
			LOG("Error %s is incorrect", a.c_str());
		}
		item_count++;
	}
	LOG("Ok %d objects read", object_count);
	LOG("Ok read %d lines from %s", item_count, filename.c_str());
	ifs.close();
}

void saveLevelToFile(const std::string& filename, std::vector<Object>* levelVector) {
	std::ofstream myfile;
	myfile.open(filename);
	myfile << "# YEZ version "<<__DATE__<<", saved on the "<<getTimeString()<<"\n";
	myfile << "# tile_sprite_id object_sprite_id collision chest_id distributor_id dps door_destitnation\n";
	for (auto it = levelVector->begin(); it != levelVector->end(); it++) {
		myfile << "i ";
		myfile << it->tile_sprite_id<< " ";
		myfile << it->object_sprite_id<< " ";
		myfile << it->collision<< " ";
		myfile << it->chest_id<< " ";
		myfile << it->distributor_id << " ";
		myfile << it->dps << " ";
		myfile << it->door_destination << "\n";
	}
	LOG("Ok level saved to file");
	myfile.close();
}

class TiledLevel: public sf::Drawable, public sf::Transformable
{
	public:
		TiledLevel() {
		objectsMap = new TileMap(0, testLevel_objects, sf::Vector2u(16, 16), 6, 6);
		std::vector<Object> objVector;
		loadLevelFromFile("level1.txt", &objVector);
		for (auto it = objVector.begin(); it != objVector.end(); it++)
			LOG("Test obj %d (%d) with %d", it->tile_sprite_id, it->collision, it->object_sprite_id);
		saveLevelToFile("level1.txt", &objVector);
		}

		~TiledLevel() {
			delete (objectsMap);
			LOG("Ok TiledLevel freed");
		}

		unsigned int getSpriteAt(size_t x, size_t y) {
			return testLevel_objects[x + y*6];
		}

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			target.draw(*objectsMap, states);
		}

	private:
		TileMap* objectsMap;

		unsigned int testLevel_objects[36] =
		{
			33, 33, 33, 33, 33, 33,
			33, 33, 33, 33, 33, 33,
			33, 33, 34, 32, 33, 33,
			33, 33, 33, 33, 33, 33,
			32, 33, 33, 33, 33, 33,
			33, 33, 33, 33, 33, 33,
		};
};

#endif // TILEDLEVEL_HPP

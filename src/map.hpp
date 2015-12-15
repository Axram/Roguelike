#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "gameobject.hpp"
#include "wall.hpp"
#include "player.hpp"

class Map{
public:
	Map(std::string filename);
	Player & get_player();
	std::vector<Gameobject*> & get_map();
	void generate_map(std::string filename);
	std::vector<Gameobject*> _go;
	std::vector<Wall*> _walls;
	Player * _player = nullptr;
	//std::vector<Enemy> _enemies;
};

#endif


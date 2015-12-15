#include "map.hpp"

Map::Map(std::string filename){

	//std::vector<Gameobject*> go;

	generate_map(filename);
}

void Map::generate_map(std::string filename){
	std::ifstream mapfile;
	mapfile.open(filename);
	std::string line;
	
	int y = 0;
	while(getline(mapfile, line)){
		int x = 0;
		//std::cout << line << std::endl;
		while(line.length() > 0){
			std::string s;
			s += line[0];
			//std::cout << "x " << x << " y " << y << " " << s <<std::endl;
			//std::cout << line.length() << std::endl;

			line.erase(line.begin());
			if(s == "#"){
				Wall * w =  new Wall(x,y);
				_go.push_back(w);
				_walls.push_back(w);
			}
			else if (s == "p"){
				Player * p = new Player(x, y);
				_go.push_back(p);
				_player = p;
			}
			else if (s == " "){
				
			}
			else{
				
			} 
			
			++x;
		}

		++y;
	}

	mapfile.close();
}
Player & Map::get_player(){
	if(_player == nullptr) throw std::out_of_range("No player found.");
	return *_player;
}

std::vector<Gameobject*> & Map::get_map(){
	return _go;
}
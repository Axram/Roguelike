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
      //TODO destruktor i map
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
      else if (s == "g"){
	Goblin * g = new Goblin(x, y);
	_go.push_back(g);
	_enemies.push_back(g);
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


bool Map::enemy_exists(int x, int y){
  for(auto i = _enemies.begin(); i != _enemies.end(); ++i){
    if((**i)._px == x && (**i)._py == y){
      return true;
    }
  }
  return false;
}
//If there is no enemy on that position we have no way to show that
//We could return a pointer insted, in which case we could return nullptr, but fuck it
Enemy & Map::get_enemy(int x, int y){
  for(auto i = _enemies.begin(); i != _enemies.end(); ++i){
    if((**i)._px == x && (**i)._py == y)
    {
      return **i;
    }
  }
}

void Map::cleanup_enemies(){
  for(auto i = _enemies.begin(); i != _enemies.end(); ++i){
    if((**i)._hp <= 0){
      delete *i;
    }
  }
}

//Called by actors to see if the grid they want to move to is occupied.
bool Map::is_free(int x, int y){
  std::vector<Gameobject> g;
  for(auto i = _go.begin(); i != _go.end(); ++i){
    if((**i)._px == x && (**i)._py == y){
      g.push_back( **i);
    }
  }
  bool is_free = true;
  for(auto i = g.begin(); i != g.end(); ++i){
    if(i->_solid){
      is_free = false;
      break;
    }
  }
  return is_free;
}

#include "map.hpp"
#include "assert.h"

Map::Map(std::string filename){

	//std::vector<Gameobject*> go;
  //_gameobjects["actors"]// = new std::vector<Gameobject*>;
	generate_map(filename);
}

Map::~Map(){
  for(auto i = _go.begin(); i != _go.end(); ++i){
    (**i)._to_be_removed = true;
  }
  cleanup();
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
        //_walls.push_back(w);

      }else if (s == "p"){
        Player * p = new Player(x, y);
        Floor * f = new Floor(x, y);
        //_gameobjects["player"].push_back(p);
        _go.push_back(p);
        _go.push_back(f);
        _player = p;
        
      }else if (s == "g"){
        Goblin * g = new Goblin(x, y);
        Floor * f = new Floor(x, y);
        //_gameobjects["actors"].push_back(g);
        _go.push_back(g);
        _go.push_back(f);
        _enemies.push_back(g);
      }else if (s == "D"){
        Door * d = new Door(x,y);
        Floor * f = new Floor(x, y);
        _go.push_back(d);
        _go.push_back(f);
        _st.push_back(d);
      }else if (s == "c"){
        Chest * d = new Chest(x,y);
        Floor * f = new Floor(x, y);
        _go.push_back(d);
        _go.push_back(f);
        _st.push_back(d);
      }else if (s == " "){ 
         Floor * f = new Floor(x, y);
         _go.push_back(f);
      }else{    
      }      
      ++x;
    }        
    ++y;
  }
    
  mapfile.close();
}
Player & Map::get_player(){
  //if(_gameobjects["player"].size() == 0)  throw std::out_of_range("No player found.");
	//return (dynamic_cast<Player>(*_gameobjects["player"][0]));
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
Enemy * Map::get_enemy(int x, int y){
  for(auto i = _enemies.begin(); i != _enemies.end(); ++i){
    if((**i)._px == x && (**i)._py == y)
    {
      return *i;
    }
  }
  return nullptr;
}

bool Map::structure_exists(int x, int y){
  for(auto i = _st.begin(); i != _st.end(); ++i){
    if((**i)._px == x && (**i)._py == y){
      return true;
    }
  }
  return false;
}

Structure * Map::get_structure(int x, int y){
  for(auto i = _st.begin(); i != _st.end(); ++i){
    if((**i)._px == x && (**i)._py == y)
    {
      return *i;
    }
  }
  return nullptr;
}

void Map::cleanup(){
  std::vector<Gameobject*> gameobjects;
  for(auto g = _go.begin(); g != _go.end(); ++g){
    if((**g)._to_be_removed){
      gameobjects.push_back(*g);
      //std::remove(_go.begin(), _go.end(), to_be_removed);//gameobjects.push_back(*g);
      
      //TODO remove the gameobjct Items in the inventory;
    }
  }
  std::vector<Enemy *> enmis;
  for(auto e = _enemies.begin(); e != _enemies.end(); ++e){
    if((**e)._to_be_removed){
      enmis.push_back(*e);
    }
  }

  std::vector<Structure*> srts;
  for(auto s = _st.begin(); s != _st.end(); ++s){
    if((**s)._to_be_removed){
      srts.push_back(*s);
    }
  }

  for(auto s = srts.begin(); s != srts.end(); ++s){
    _st.erase(std::remove(_st.begin(), _st.end(), (*s)), _st.end());
  }

  for(auto e = enmis.begin(); e != enmis.end(); ++e){
    
    _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), (*e)), _enemies.end());
  }
  for(auto g = gameobjects.begin(); g != gameobjects.end(); ++g){
    delete(*g);
    _go.erase(std::remove(_go.begin(), _go.end(), (*g)), _go.end());
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

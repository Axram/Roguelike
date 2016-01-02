#include "map.hpp"
#include "assert.h"

Map::Map(std::string filename, WINDOW*& text){

  _textbox = text;
  generate_map(filename);
  //save_data();
  //load_data();
}

Map::~Map(){
  for(auto i = _go.begin(); i != _go.end(); ++i){
    (**i).remove();
  }
  cleanup();
}

void Map::generate_map(std::string filename){
  std::ifstream mapfile;
  mapfile.open(filename);
  std::string line;
	int item_nr = 0;
  int y = 0;
  while(getline(mapfile, line)){
    int x = 0;

    while(line.length() > 0){
      std::string s;
      s += line[0];

          
      line.erase(line.begin());
      //TODO destruktor i map
      if(s == "#"){
        Wall * w =  new Wall(x,y);
        _go.push_back(w);


      }else if (s == "p"){
        Player * p = new Player(x, y, _textbox);
        Floor * f = new Floor(x, y);
        load_inventory(p->get_inventory(), "maps/map2_info.txt" ,item_nr);
        _go.push_back(p);
        _go.push_back(f);
        _player = p;
        
      }else if (s == "g"){
        Goblin * g = new Goblin(x, y, _textbox);
        Floor * f = new Floor(x, y);
        load_inventory(g->get_inventory(), "maps/map2_info.txt" ,item_nr);

        _go.push_back(g);
        _go.push_back(f);
        _enemies.push_back(g);
      }else if (s == "D"){
        Door * d = new Door(x,y, _textbox);
        Floor * f = new Floor(x, y);
        _go.push_back(d);
        _go.push_back(f);
        _st.push_back(d);
      }else if (s == "c"){
        Chest * d = new Chest(x,y, _textbox);
        Floor * f = new Floor(x, y);
        load_inventory(d->get_inventory(), "maps/map2_info.txt" ,item_nr);
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

void Map::save_data(){
  std::ofstream file;
  file.open("maps/map_savedata.txt");
  for(auto i = _go.begin(); i != _go.end(); ++i){
    //file << '$';
    std::string data = (**i).get_data();
    file << data;
  }
  file.close();
}
void Map::load_data(){
  std::ifstream file;
  file.open("maps/map_savedata.txt");
  std::string line;
  while(getline(file, line)){
    if(line[0] == '#') continue;
    std::string key = line;
    getline(file, line); //px
    int px = atoi(line.c_str());
    getline(file, line); //py
    int py = atoi(line.c_str());
    Actor * actor = nullptr;
    if(key == "Wall"){
      Wall * item = new Wall(px, py);
      _go.push_back(item);
    }else if(key == "Player"){
      Player * item = new Player(px, py, _textbox);
      actor = item;
      _go.push_back(item);
      _player = item;
    }else if(key == "Goblin"){
      Goblin * item = new Goblin(px, py, _textbox);
      actor = item;
      _go.push_back(item);
      _enemies.push_back(item);
    }else if(key == "Door"){
      Door * item = new Door(px, py, _textbox);
      getline(file, line);
      item->_solid = atoi(line.c_str());
      _go.push_back(item);
      _st.push_back(item);      
    }else if(key == "Floor"){
      Floor * item = new Floor(px, py);
      _go.push_back(item);
    }else if(key == "Chest"){
      Chest * item = new Chest(px, py, _textbox);
      getline(file, line);
      while(line != "$"){
        add_item(item->get_inventory(), line);
        getline(file, line);
      }
      _go.push_back(item);
      _st.push_back(item);
    }

    if(actor != nullptr){ //All actors
      getline(file, line);
      int hp = atoi(line.c_str());
      actor->_hp = hp;
      getline(file, line);
      int xp = atoi(line.c_str());
      actor->_experience = xp;
      getline(file, line);
      while(line != "$"){
        add_item(actor->get_inventory(), line);
              getline(file, line);

      }
    }
  }
  file.close();
}
void Map::add_item(std::vector<Item*>* inventory, std::string name){
  if(name == "Doorkey"){
    Doorkey * dk = new Doorkey();
    inventory->push_back(dk);
  }
}
Player * Map::get_player(){

	if(_player == nullptr) throw std::out_of_range("No player found.");
  return _player;
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
std::vector<Enemy*> & Map::get_enemies(){
  return _enemies;
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
  //As we do have multiple pointers to the same objects this needs extra care
  //Firstly all pointers that are to be removed are copied
  std::vector<Gameobject*> gameobjects_to_remove;
  for(auto g = _go.begin(); g != _go.end(); ++g){
    if((**g).get_to_be_removed()){

      gameobjects_to_remove.push_back(*g);
    }
  }
  std::vector<Enemy *> enemies_to_remove;
  for(auto e = _enemies.begin(); e != _enemies.end(); ++e){
    if((**e).get_to_be_removed()){
      enemies_to_remove.push_back(*e);

    }
  }

  std::vector<Structure*> structures_to_remove;
  for(auto s = _st.begin(); s != _st.end(); ++s){
    if((**s).get_to_be_removed()){
      structures_to_remove.push_back(*s);

    }
  }
  //Secondly they are removed

  for(auto s = structures_to_remove.begin(); s != structures_to_remove.end(); ++s){
    _st.erase(std::remove(_st.begin(), _st.end(), (*s)), _st.end());
  }

  for(auto e = enemies_to_remove.begin(); e != enemies_to_remove.end(); ++e){
    
    _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), (*e)), _enemies.end());
  }

  //Thirdly the objects are deleted and the final pointer is removed.
  for(auto g = gameobjects_to_remove.begin(); g != gameobjects_to_remove.end(); ++g){
    delete(*g);
    _go.erase(std::remove(_go.begin(), _go.end(), (*g)), _go.end());
  }

}

//TODO make is_free safe if coordinate with no gameobject is called (return false)
//Called by actors to see if the grid they want to move to is occupied.
bool Map::is_free(int x, int y){
  //std::cout << "In is free" << std::endl;
  std::vector<Gameobject> g;
  for(auto i = _go.begin(); i != _go.end(); ++i){
    if((**i)._px == x && (**i)._py == y){
      g.push_back( **i);
    }
  }

  //std::cout << "Is still in is free" << std::endl;
  bool is_free = true;
  for(auto i = g.begin(); i != g.end(); ++i){
    if(i->get_solid()){
      is_free = false;
      break;
    }
  }
  return is_free;
}
void Map::load_inventory(std::vector<Item*>* inventory, std::string filename, int & item_nr){
  std::ifstream mapfile;
  mapfile.open(filename);
  std::string line;
  int nr = -1;
  int y = 0;
  while(getline(mapfile, line)){
    if(line[0] == '#') continue;
    if(line[0] == '$') {
      nr++;
    }else if(nr == item_nr){
      if(line == "doorkey") {
        Doorkey * item = new Doorkey();
        inventory->push_back(item);
      }
    }
    if(nr > item_nr){
      break;
    }
  }
  item_nr++;
}
//Finds a good path from hunter to target and moves hunter one space
//This will only try to move directly towards the player and will get stuck in walls
void Map::find_path(Actor & hunter, Gameobject & target){
  int diffx = target._px-hunter._px;
  int diffy = target._py-hunter._py;

  int distance = int (std::sqrt(diffx*diffx + diffy*diffy));
if(distance < 6){ //Arbitary number to avoid everyone chasing the player all the time
    int diffx_normalized = diffx/distance;
    int diffy_normalized = diffy/distance;
    if(std::abs(diffx_normalized) > std::abs(diffy_normalized) && is_free(hunter._px + diffx_normalized, hunter._py)){
      hunter.move(diffx_normalized, 0);
    }
    else if(is_free(hunter._px, hunter._py + diffy_normalized)){
      hunter.move(0, diffy_normalized);
    }
  }
}
#include "map.hpp"
#include "assert.h"

Map::Map(std::string filename, WINDOW*& text){
  _textbox = text;
  std::string premade = "maps/"+ filename +".txt";
  std::string save = "maps/"+filename +".savegame";
 _funkpoint["#"] =  &Map::add_wall;
 _funkpoint["p"] =  &Map::add_player;
 _funkpoint["g"] =  &Map::add_goblin;
 _funkpoint["D"] =  &Map::add_door;
 _funkpoint["c"] =  &Map::add_chest;
 _funkpoint[" "] = &Map::add_floor;
 if(filename == "secretlegacy"){
  generate_map("map2");
 }else if(FILE *file = fopen(premade.c_str(),"r")){
    fclose(file);
    load_data_new(premade);
  }else if(FILE *file = fopen(save.c_str(),"r")){
    fclose(file);
    load_data_new(save);
  }else{
    throw std::out_of_range("No file named" + filename + "found");
  }
}

Map::~Map(){
  _cleaning_up = true;
  for(auto i = _go.begin(); i != _go.end(); ++i){
    (**i).remove();
  }
  cleanup();
}



void Map::generate_map(std::string filename){
  std::ifstream mapfile;
  mapfile.open("maps/" + filename + ".txt");
  std::string item_filename = "maps/"+ filename+"_info.txt";
  std::string line;
	int item_nr = 0;
  std::map<std::string, void *> helo;
  int y = 0;
  while(getline(mapfile, line)){
    int x = 0;

    while(line.length() > 0){
      std::string s;
      s += line[0];
      line.erase(line.begin());
      if(_funkpoint.count(s) != 0)(this->*_funkpoint[s])(x,y,item_nr, item_filename);   
      ++x;
    }        
    ++y;
  }
    
  mapfile.close();
}

void Map::save_data(std::string your_name){
  std::ofstream file;
  std::string filename = "maps/" + your_name + ".savegame";
  remove(filename.c_str());
  file.open(filename);
  for(auto i = _go.begin(); i != _go.end(); ++i){
    //file << '$';
    std::string data = (**i).get_data();
    file << data;
  }
  file.close();
}
void Map::save_data_new(std::string name){
  std::ofstream file;
  std::ofstream debugfile;
  debugfile.open("save_log.txt");
  debugfile << "saving map..." << std::endl;
  std::string filename = "maps/" + name + ".savegame";
  debugfile << "filename " << filename << std::endl;

  remove(filename.c_str());
  file.open(filename);
  for(auto i = _go.begin(); i != _go.end(); ++i){
    //file << '$';
    debugfile << "getting item " << (**i).get_name() << std::endl;
    std::string data = (**i).get_data_new();
    if((**i).get_name() == "Goblin" || (**i).get_name() == "Mario") debugfile << data << std::endl;
    file << data;
  }
  debugfile << "done!" << std::endl;
  debugfile.close();
  file.close();
}

void Map::load_data_new(std::string filename){
  std::ifstream file;
  std::ofstream debugfile;
  debugfile.open("load_log.txt");
  debugfile << "loading map..." << std::endl;
  debugfile << "filename " << filename << std::endl;
  file.open(filename);
  std::string line;
  std::string type;
  while(getline(file, line)){
    type = line;
    getline(file, line); 
    int px = atoi(line.c_str());
    getline(file, line); 
    int py = atoi(line.c_str());
    getline(file, line); 
    int depth = atoi(line.c_str());
    getline(file, line); 
    std::string name = line;
    getline(file, line); 
    std::string desc = line;
    getline(file, line); 
    std::string img = line;
    getline(file, line); 
    bool solid;
    if(line == "True"){solid = true;}else{solid = false;}
    getline(file, line); 
    bool movable;
    if(line == "True"){movable = true;}else{movable = false;}

    Gameobject * gameobject;

    if(type == "Player" || type == "Enemy" || type == "Npc"){
      debugfile << "Actor!" << std::endl;
      getline(file, line); 
      int hp = atoi(line.c_str());
      getline(file, line); 
      int attack = atoi(line.c_str());
      getline(file, line); 
      int defense = atoi(line.c_str());
      getline(file, line);
      int experience = atoi(line.c_str());
      getline(file, line); 
      int exp_worth = atoi(line.c_str());
      getline(file, line); 
      int speed = atoi(line.c_str());
      getline(file, line); 
      int speed_c = atoi(line.c_str());
      Actor * actor;
      if(type == "Player"){
        Player * player = new Player(hp, attack, defense, experience, exp_worth, speed, speed_c);
        debugfile << "- and PLayer!" << std::endl;
        gameobject = player;
        actor = player;
        _player = player;
      }else if (type == "Enemy"){
        Enemy * enemy = new Enemy(hp, attack, defense, experience, exp_worth, speed, speed_c);
        _enemies.push_back(enemy);
        gameobject = enemy;
        actor = enemy;
      }else if(type == "Npc"){
        Npc * npc = new Npc(hp, attack, defense, experience, exp_worth, speed, speed_c);
        _npcs.push_back(npc);
        gameobject = npc;
        actor = npc;
      }else {
        throw std::out_of_range("type " + type + " does not exist");
      }
      debugfile << hp << " hp" << std::endl;
      getline(file, line);
      while(line != "$"){
        Item * item = new Item(line);
        actor->add_item(item);
        debugfile << "with item: " << line << std::endl;
        getline(file, line);
      }
    }else if(type == "Gameobject"){
      gameobject = new Gameobject();
      debugfile << "Gameobject!" << std::endl;
    }else if(type == "Chest"){
      debugfile << "Chest!" << std::endl;
      Chest * chest = new Chest(px, py, _textbox);
      gameobject = chest;
      _st.push_back(chest);
      getline(file, line);
      while(line != "$"){
        Item * item = new Item(line);
        chest->add_item(item);
        debugfile << "with item: " << line << std::endl;
        getline(file, line);
      }
    }else if(type == "Door"){
      Door * door = new Door(px, py, _textbox);
      _st.push_back(door);
      gameobject = door;
    }else if(type == "Altar"){
      
      Altar * altar = new Altar(px, py, _textbox);
      _st.push_back(altar);
      gameobject = altar;
      
    }else{
      debugfile << "Error " << type << " not found!" << std::endl;
      debugfile.close();
      assert(false);
    }
    gameobject->set_vars(type, px, py, depth, name, desc, img[0], solid, movable, _textbox);
    debugfile << "name " << name<< std::endl;
    debugfile << "px "<<px << std::endl;
    debugfile << "py" << py<< std::endl;
    _go.push_back(gameobject);
  }
  debugfile << "done! " << std::endl;
  debugfile.close();
  file.close();
}

void Map::spawn_chest(Actor * someone){
  if(!_cleaning_up){
    if(someone->get_inventory()->size() != 0){
      Chest * chest = new Chest(someone->_px, someone->_py, _textbox, true);
      _go.push_back(chest);
      _st.push_back(chest);
      for(auto i = someone->get_inventory()->begin(); i != someone->get_inventory()->end(); ++i){
        chest->get_inventory()->push_back(*i);
      }
    }
  }else {
    someone->remove_items();
  }
}
void Map::add_item(std::vector<Item*>* inventory, std::string name){
  if(name == "Doorkey" || name == "doorkey"){
    Doorkey * dk = new Doorkey();
    inventory->push_back(dk);
  }
  if(name == "WINITEM" || name == "Winitem" || name == "winitem"){
    Winitem * win = new Winitem();
    inventory->push_back(win);
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
std::vector<Npc*> * Map::get_npcs(){
  return  &_npcs;
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
  //Firstly all pointerget_gameobjs that are to be removed are copied
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

  std::vector<Npc*> npcs_to_remove;
  for(auto n = _npcs.begin(); n != _npcs.end(); ++n){
    if((**n).get_to_be_removed()){
      npcs_to_remove.push_back(*n);
    }
  }
  //Secondly they are removed

  for(auto s = structures_to_remove.begin(); s != structures_to_remove.end(); ++s){
    _st.erase(std::remove(_st.begin(), _st.end(), (*s)), _st.end());
  }

  for(auto e = enemies_to_remove.begin(); e != enemies_to_remove.end(); ++e){
    spawn_chest(*e);
    _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), (*e)), _enemies.end());
    
  }
  for(auto n = npcs_to_remove.begin(); n != npcs_to_remove.end(); ++n){
    spawn_chest(*n);
    _npcs.erase(std::remove(_npcs.begin(), _npcs.end(), (*n)), _npcs.end());
    
  }

  if(_player->get_to_be_removed())_player->remove_items();
  //Thirdly the objects are deleted and the final pointer is removed.
  for(auto g = gameobjects_to_remove.begin(); g != gameobjects_to_remove.end(); ++g){
    delete(*g);
    _go.erase(std::remove(_go.begin(), _go.end(), (*g)), _go.end());
  }

}

//TODO make is_free safe if coordinate with no gameobject is called (return false)
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
  while(getline(mapfile, line)){
    if(line[0] == '#') continue;
    if(line[0] == '$') {
      nr++;
    }else if(nr == item_nr){
      if(line == "doorkey") {
        Doorkey * item = new Doorkey();
        inventory->push_back(item);
      }else if(line == "WINITEM"){
        Winitem * item = new Winitem();
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
    int diffx_normalized; 
    int diffy_normalized;
    distance != 0 ? diffx_normalized = diffx/distance : diffx_normalized = 1;
    distance != 0 ? diffy_normalized = diffy/distance : diffy_normalized = 1;
    if(std::abs(diffx_normalized) > std::abs(diffy_normalized) && is_free(hunter._px + diffx_normalized, hunter._py)){
      hunter.move(diffx_normalized, 0);
    }
    else if(is_free(hunter._px, hunter._py + diffy_normalized)){
      hunter.move(0, diffy_normalized);
    }
  }
}
void Map::add_wall(int px, int py, int& item_nr, std::string){
  Wall * wall = new Wall(px, py);
  _go.push_back(wall);
}

void Map::add_player(int x, int y, int& item_nr, std::string item_filename){
  Player * p = new Player(x, y, _textbox);
  Floor * f = new Floor(x, y);
  load_inventory(p->get_inventory(), item_filename ,item_nr);
  _go.push_back(p);
  _go.push_back(f);
  _player = p;

}
void Map::add_chest(int x, int y , int& item_nr, std::string item_filename){
  Chest * d = new Chest(x,y, _textbox);
  Floor * f = new Floor(x, y);
  load_inventory(d->get_inventory(), item_filename ,item_nr);
  _go.push_back(d);
  _go.push_back(f);
  _st.push_back(d);
}
void Map::add_goblin(int x, int y, int& item_nr, std::string item_filename){
  Goblin * g = new Goblin(x, y, _textbox);
  Floor * f = new Floor(x, y);
  load_inventory(g->get_inventory(), item_filename ,item_nr);
  _go.push_back(g);
  _go.push_back(f);
  _enemies.push_back(g);
}
void Map::add_door(int x, int y , int& item_nr, std::string item_filename){
  Door * d = new Door(x,y, _textbox);
  Floor * f = new Floor(x, y);
  _go.push_back(d);
  _go.push_back(f);
  _st.push_back(d);
}
void Map::add_floor(int x, int y, int& item_nr, std::string item_filename){
  Floor * f = new Floor(x, y);
  _go.push_back(f);
}
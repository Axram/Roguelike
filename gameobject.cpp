#include <string>

struct Pos{
  int x;
  int y;
};

class Gameobject{
public:

  Gameobject(){}
  Gameobject(int px, int py){
    _pos.x = px;
    _pos.y = py;
  }
  Gameobject(int px, int py, std::string img){
    _pos.x = px;
    _pos.y = py;  
    _img = img;
  }
  Gameobject(int px, int py, std::string img, std::string name, std::string desc){
    _pos.x = px; 
    _pos.y = py;
    _img = img;
    _name = name;
    _description = desc;
  }
  Gameobject(int px, int py, std::string img, bool solid, bool movable){
    _pos.x = px;
    _pos.y = py;
    _img = img;
    _solid = solid;
    _movable = movable;
  }
  Gameobject(int px, int py, std::string img, bool solid, bool movable, std::string name, std::string desc){
    _pos.x = px;
    _pos.y = py;
    _img = img;
    _solid = solid;
    _movable = movable;
    _name = name;
    _description = desc;
  }
  struct Pos _pos;
  bool _solid = true;
  bool _movable = false;
  std::string _name = "Nobody";
  std::string _description = "Caped baldy";
  std::string _img = "@";
private:

  /*
    Position (posx, posy)
    Visuell Representation ("@")
    Solid/Kan gås igenom (solid = true)
    Namn (name = "Troll")
    Beskrivning ("A smelly troll") 
   */

};




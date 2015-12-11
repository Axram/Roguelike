#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <string>
struct Pos{
  int x;
  int y;
}

  /*
    Position (posx, posy)
    Visuell Representation ("@")
    Solid/Kan gås igenom (solid = true)
    Namn (name = "Troll")
    Beskrivning ("A smelly troll") 
   */




class Gameobject{
public:
  //Constructors
  Gameobject();
  Gameobject(int px, int py);
  Gameobject(int px, int py, char img, bool solid, bool movable, std::string name, std::string desc);

  //Member variables 
  Pos _pos;
  bool _solid = true;
  bool _movable = true;
  std::string _name = "Nobody";
  std::string _desc = "Caped baldy";
  char _img = '@';
private:


};
#endif

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <string>
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
  Gameobject(int px, int py, int depth, char img, bool solid, bool movable, std::string name, std::string desc);
  bool operator<(const Gameobject & b);
  //Member variables 
  int _px;
  int _py;
  int _depth;
  bool _solid = true;
  bool _movable = true;
  std::string _name = "Nobody";
  std::string _desc = "Caped baldy";
  char _img = '@';
private:


};
#endif

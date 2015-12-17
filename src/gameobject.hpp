#pragma once
#include <string>

class Gameobject{
public:
  //Constructors
  Gameobject();
  Gameobject(int px, int py);
  Gameobject(int px, int py, int depth, char img, bool solid, bool movable, std::string name, std::string desc);
  virtual ~Gameobject();
  bool operator<(const Gameobject & b);
  //Member variables

  int _px = 0;
  int _py = 0;
  int _depth = 1;
  bool _solid = true; //Can the object be collided with?
  bool _movable = true; //Can the object be moved?
  bool _to_be_removed = false; 
  std::string _name = "Nobody";
  std::string _desc = "Caped baldy";
  char _img = '@';
private:


};


#pragma once
#include <string>

#include <ncurses.h>
//#include "textbox.hpp"

class Gameobject{
public:
  //Constructors
  Gameobject();
  //Gameobject(std::string type, int px, int py, int depth, std::string name, std::string desc, char img, bool solid, bool movable);
  virtual ~Gameobject();
  bool operator<(const Gameobject & b);
  char get_img()const;
  int get_depth()const;
  bool get_solid()const;
  std::string get_name()const;
  std::string get_desc()const;
  bool get_to_be_removed()const;
  bool is_near_me(const Gameobject & other)const;
  void remove(); //Now it's only possible to set _to_be removed to true. You can't undo. Hopefully we'll never want to.
  //Member variables
  void set_vars(const std::string& type, int px, int py, int depth, const std::string& name, const std::string& desc, char img, bool solid, bool movable, WINDOW * text);
  virtual std::string get_data();
  virtual std::string get_data_new();
  int _px = 0; //These are public as we both want to get and set these without caring.
  int _py = 0;

protected:
  WINDOW * _textbox = nullptr;
  std::string _type;
  int _depth = 1;
  bool _solid = true; //Can the object be collided with?
  bool _movable = true; //Can the object be moved?
  bool _to_be_removed = false; 
  std::string _name = "Nobody";
  std::string _desc = "Caped baldy";
  char _img = '@';
private:
};


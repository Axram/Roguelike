#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <ncurses.h>

#include "gameobject.hpp"
#include "item.hpp"

class Structure:public Gameobject{
public:
  Structure();
  virtual bool interact(std::vector<Item *>* inventory);
protected:
  virtual bool move();
  virtual void destroy();	
};
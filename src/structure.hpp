#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "gameobject.hpp"

class Structure:public Gameobject{
public:
  Structure();
protected:
  virtual bool move();
  virtual bool interact(Structure & target); 
  virtual void die();	
};
#pragma once

#include "npc.hpp"

class Enemy:public Npc{ 
//Finns för att indentifiera en fiende, så vi kan lätt hitta saker vi bör anfalla
public:
  Enemy();
  Enemy(int hp, int attack, int defense, int experience, int exp_worth, int speed, int speed_c );
  using Actor::Actor;
  Enemy(int, int, WINDOW * text);
  virtual void patrol(); //temp
  virtual void wait(); //temp
  virtual void find_path(int x, int y) override;
private:
  
};

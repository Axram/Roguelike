#pragma once

#include "npc.hpp"

//TODO borde vi kombinera npc och enemy?
class Enemy:public Npc{ 
//Finns för att indentifiera en fiende, så vi kan lätt hitta saker vi bör anfalla
//Ska ärvas så vi gör mer specifika klasser som "Goblin" eller "Spooky Skeleton"
public:
  Enemy();
  Enemy(int px, int py, int depth, char icon, int hp, int attack, int defense, std::string name, std::string desc);
  //Ska ha en unik pathfinding så att den jagar spelaren?
  virtual void patrol(); //temp
  virtual void wait(); //temp
  virtual void find_path(int x, int y) override;
private:
  
};

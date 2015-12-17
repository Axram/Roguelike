#include "npc.hpp"

Npc::Npc(){}
Npc::Npc(int px, int py, int depth,char icon, int hp, int attack, int defense, std::string name, std::string desc):Actor(px, py, depth,icon, hp, attack, defense, name, desc){}
void Npc::find_path(int x, int y){} //TODO define/remove find_path


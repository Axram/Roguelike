#include "npc.hpp"
Npc::Npc(){}
Npc::Npc(int px, int py, WINDOW * text){
	_px = px;
	_py = py;
	_textbox = text;
}
Npc::Npc(int hp, int attack, int defense, int experience, int exp_worth, int speed, int speed_c ){
  _hp = hp;
  _attack = attack;
  _defense = defense;
  _experience = experience;
  _experience_worth = exp_worth;
  _speed = speed; 
  _speed_counter = speed_c;

}
void Npc::find_path(int target_x, int target_y){

}
void Npc::roam(){}
bool Npc::is_roaming(){
	return _roaming;
}
#include "enemy.hpp"

Enemy::Enemy(){}
Enemy::Enemy(int px, int py, WINDOW * text){
	_px = px;
	_py = py;
	_textbox = text;
}
Enemy::Enemy(int hp, int attack, int defense, int experience, int exp_worth, int speed, int speed_c ){
  _hp = hp;
  _attack = attack;
  _defense = defense;
  _experience = experience;
  _experience_worth = exp_worth;
  _speed = speed; 
  _speed_counter = speed_c;

}
void Enemy::patrol(){}
void Enemy::wait(){}
void Enemy::find_path(int x, int y){}

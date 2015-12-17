#include "enemy.hpp"

Enemy::Enemy(){}
Enemy::Enemy(int px, int py, int depth, char icon, int hp, int attack, int defense, std::string name, std::string desc):Npc(px, py, depth, icon, hp, attack, defense, name, desc){}
//Had to create these as they where virtual
void Enemy::patrol(){}//TODO define/remove patrol
void Enemy::wait(){}//TODO define/remove wait
void Enemy::find_path(int x, int y){} //TODO define/remove find_path

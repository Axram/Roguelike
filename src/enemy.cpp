#include "enemy.hpp"

Enemy::Enemy(){}
Enemy::Enemy(int px, int py, WINDOW * text){
	_px = px;
	_py = py;
	_textbox = text;
}
//Had to create these as they where virtual
void Enemy::patrol(){}//TODO define/remove patrol
void Enemy::wait(){}//TODO define/remove wait
void Enemy::find_path(int x, int y){} //TODO define/remove find_path

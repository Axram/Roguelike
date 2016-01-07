#include "enemy.hpp"

Enemy::Enemy(){}
Enemy::Enemy(int px, int py, WINDOW * text){
	_px = px;
	_py = py;
	_textbox = text;
}
void Enemy::patrol(){}
void Enemy::wait(){}
void Enemy::find_path(int x, int y){}

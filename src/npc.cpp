#include "npc.hpp"
Npc::Npc(){}
Npc::Npc(int px, int py, WINDOW * text){//:_px(px), _py(py), _textbox(text){
	_px = px;
	_py = py;
	_textbox = text;
}
void Npc::find_path(int target_x, int target_y){
	//Currently in map

}
void Npc::roam(){}
bool Npc::is_roaming(){
	return _roaming;
}
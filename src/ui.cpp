#include "ui.hpp"
Ui::Ui(){}
Ui::~Ui(){}

WINDOW* Ui::create_newwin(int height, int width, int starty, int startx){}
void Ui::destroy_win(WINDOW* local_win){}
void Ui::ui_print(Map* whole_map, WINDOW* gamebox){}
void Ui::inv_print(Player * p, WINDOW* inventbox){}

//Not member function
bool nui_comp(const Gameobject* a, const Gameobject* b){}
#include "textbox.hpp"

Textbox::Textbox(int px, int py, int sizex, int sizey):_px(px), _py(py), _size_x(sizex), _size_y(sizey){
  std::cout << _py << std::endl;
}


void Textbox::set_cursor(int px, int py){
  ++px;
  ++py;
  std::cout << "\33["<<py<<";"<<px<<"H";
}

void Textbox::add_row(std::string new_row){
  _rows.push_back(new_row);
  if(_rows.size() > _size_y){
    _rows.erase(_rows.begin());
  }
}

void Textbox::print(){
  std::string s;
  set_cursor(_px, _py);
  for(auto i = _rows.begin(); i != _rows.end(); ++i){
    for(int x  = 0; x < i->size(); ++x){
      s+= (*i)[x];
      if(x >= _size_x)break;
    }
    s+= '\n';
  }
  if(s.length() != 0)s.pop_back();
  std::cout << s;
  set_cursor(_px, _py+_size_y);
}

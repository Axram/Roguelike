#include "item.hpp"
Item::Item(){}
Item::Item(std::string name):_name(name){}
std::string Item::get_name(){
  return _name;
}
int Item::get_weight(){
  return _weight;
}
std::string Item::get_description(){
  return _description;
}



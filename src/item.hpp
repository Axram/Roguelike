#pragma once

#include <string>

class Item{
public:
  Item();
	Item(std::string);
  ~Item(){}
  std::string get_name();
  int get_weight();
  std::string get_description();
protected:
    std::string _name = "";
    int _weight = 0;
    std::string _description = "";


	bool use(){return false;}

};


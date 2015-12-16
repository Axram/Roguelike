#pragma once
#include <vector>
#include <string>
#include <iostream>
//Shows text in an orderly fashion
//Everytime something wants to print it calls textbox's add_row
//Too old rows are deleted //TODO spara alla gamla rader så man kan scrolla tillbaka
//If the print is too wide it's truncated //TODO fixa så det blir ett radbyte istället (fixa i add_row)
class Textbox{
public:
  Textbox(int px, int py, int sizex, int sizey);
  void add_row(std::string);
  void print();
private:
  void set_cursor(int px, int py);
  int _px;
  int _py;
  int _size_x; //Max amount of letters wide
  int _size_y; //Max amount of rows
  std::vector<std::string> _rows;

};

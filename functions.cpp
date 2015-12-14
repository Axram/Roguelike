#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP
#include <string>
#include <iostream>
template<typename T> void PRINT(std::string, T); //simple print, sorry for making it all caps
#endif	
template<typename T>
void PRINT(std::string s, T t){
	std::cout << s << " " << t << "." << std::endl;
}

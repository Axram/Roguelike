#pragma once

#include <string>

class Item{
public:
	//virtual ~Item() = 0;
	~Item(){}
    std::string _name = "";
    int _weight = 0;//
    std::string _description = "";


	bool use(){}// = 0;
    //= uppplockningsfunktion
    //Resten ligger i arv


};

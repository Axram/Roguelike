#include "doorkey.hpp"

bool Doorkey::use(){
	--uses;
	return false;
}
#include "Exstar/Utils/Exception.h"
exstar::exception::exception(std::string message){
	std::cerr << message << std::endl;
}
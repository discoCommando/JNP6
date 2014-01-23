#include <iostream>
#include <memory>
#include "mojagrubaryba.h"

int main(){
	std::shared_ptr<PlayerFactory> f = std::shared_ptr<PlayerFactory>(new ConcretePlayerFactory()); 
	return 0;
}

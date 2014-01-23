#include <iostream>
#include <memory>
#include "mojagrubaryba.h"

int main(){
	std::shared_ptr<PlayerFactory> f(new ConcretePlayerFactory()); 
	return 0;
}

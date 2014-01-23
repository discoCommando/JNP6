#include <iostream>
#include <memory>
#include "mojagrubaryba.h"

int main()
{
	 std::shared_ptr<MojaGrubaRyba> mgr = std::shared_ptr<MojaGrubaRyba>(new MojaGrubaRyba());
   
	std::shared_ptr<PlayerFactory> f = std::shared_ptr<PlayerFactory>(new ConcretePlayerFactory() ); 
	//std::shared_ptr<ConcretePlayerFactory> d = std::shared_ptr<ConcretePlayerFactory>(new ConcretePlayerFactory() ); 
	return 0;
}

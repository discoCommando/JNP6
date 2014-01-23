#include <iostream>
#include <memory>
#include "mojagrubaryba.h"
int main()
{
   
	std::shared_ptr<PlayerFactory> f = std::shared_ptr<PlayerFactory>(new ConcretePlayerFactory() ); 
	f->registerComputerPlayer(GrubaRyba::ComputerLevel::DUMB, std::shared_ptr<ComputerPlayer>(new DumbComputerPlayer("prototype")));
	std::shared_ptr<ComputerPlayer> p = f->createComputerPlayer(GrubaRyba::ComputerLevel::DUMB, "gracz1");

	return 0;
}

#include "mojagrubaryba.h"

MojaGrubaRyba::MojaGrubaRyba()
{

}
	
void Board::addField(std::shared_ptr<Field> newField)
{
	Fields.push_back(newField);
}

int Board::sizeOfBoard() const
{
	return Fields.size();
}

MGRBoard::MGRBoard()
{
	Board::addField( std::shared_ptr<Field>(new Start("Start")));
	
	Board::addField( std::shared_ptr<Field>(new Coral("Anemonia", priceOfAnemonia)));
	
	Board::addField( std::shared_ptr<Field>(new Field("Wyspa")));
	
	Board::addField( std::shared_ptr<Field>(new Coral("Aporina", priceOfAporina)));
	
	Board::addField( std::shared_ptr<Field>(new Aquarium("Akwarium", aquaWait)));
	
	Board::addField( std::shared_ptr<Field>(new PublicProperty("Grota", priceOfGrota)));
	
	Board::addField( std::shared_ptr<Field>(new Coral("Menella", priceOfMenella)));
	
	Board::addField( std::shared_ptr<Field>(new Deposit("Laguna", priceOfPayLaguna)));
	
	Board::addField( std::shared_ptr<Field>(new PublicProperty("Statek", priceOfStatek)));
	
	Board::addField( std::shared_ptr<Field>(new Reward("Blazenki", rewardBlazenki)));
	
	Board::addField( std::shared_ptr<Field>(new Coral("Pennatula", priceOfPennatula)));
	
	Board::addField( std::shared_ptr<Field>(new Punishment("Rekin", priceOfPayRekin)));
	
}


void Field::stepOn(std::shared_ptr<Player> p){}
void Field::goThrough(std::shared_ptr<Player> p){}
bool Field::permissionToMove(std::shared_ptr<Player> p)
{
	return true;
}
void Field::endOfRound()
{

}
const std::string& Field::getName()
{
	return this->name;
}



void Start::stepOn(std::shared_ptr<Player> p)
{
	p->giveCash(startPrice);
}
void Start::goThrough(std::shared_ptr<Player> p)
{
	Start::stepOn(p);
}


void Reward::stepOn(std::shared_ptr< Player > p)
{
	p->giveCash(this->reward);
}


void Punishment::stepOn(std::shared_ptr< Player > p)
{
	//TODO rzucic wyjatek jesli p->takeCash(this->punishmentPrice) < punishmentPrice (to znaczy ze zbankrutowal)
	p->takeCash(this->punishmentPrice);
}


void Deposit::goThrough(std::shared_ptr< Player > p)
{
	//TODO to samo co wyzej
	cash += p->giveCash(this->payPrice);
}
void Deposit::stepOn(std::shared_ptr< Player > p)
{
	p->giveCash(this->cash);
	cash = 0;
}

void Aquarium::stepOn(std::shared_ptr< Player > p)
{
	this->waitingPlayers[p] = this->waitTime;
}
bool Aquarium::permissionToMove(std::shared_ptr< Player > p)
{
	auto it = waitingPlayers.find(p);
	if (it->second == 0)
	{
		waitingPlayers.erase(it);
		return true;
	}
	return false;
}
void Aquarium::endOfRound()
{
	for(auto it = waitingPlayers.begin(); it != waitingPlayers.end(); it++)
	{
		it->second--;
	}
}

void Property::stepOn(std::shared_ptr< Player > p)
{
	//TODO WYJATKIIIII
	this->Owner->takeCash(p->giveCash(this->priceOfStay));
}

bool Property::noOwner()
{
	if (this->Owner)
		return true;
	return false;
}


int Player::getPos()
{
	return this->position;
}

void Player::takeCash(int _cash)
{
	this->cash += _cash;
}

int Player::getCash()
{
	return this->cash;
}

int Player::giveCash(int _cash)
{
	auto it = this->myProperties.begin();
// 	while ((this->cash < _cash) && (it != this->myProperties.end()))
// 	{
// 		if(this->wantSell(it.))
// 	}
}





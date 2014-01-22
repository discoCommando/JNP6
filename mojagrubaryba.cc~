#include "mojagrubaryba.h"

MojaGrubaRyba::MojaGrubaRyba()
{

}
<<<<<<< HEAD

void MojaGrubaRyba::play(unsigned int rounds)
{
		unsigned int counter = 0;
		while((++counter <= rounds) && (this->Players.size() > 1))
		{
			makeRound();
		}
}

void MojaGrubaRyba::makeRound()
{
		for(int i = 0; i < Players.size(); i++)
		{
			makeMove(Players[i]);
		}
}


void MojaGrubaRyba::makeMove(std::shared_ptr<Player> p)
{
		if(this->myBoard->getField(p->getPos())->permissionToMove(p))
		{
				int roll = this->defaultDie->roll() + this->defaultDie->roll();
				int pos = p->getPos();
				for(int i = 0; i < roll - 1; i++)
				{
					pos = (pos + 1)%this->myBoard->sizeOfBoard();
					this->myBoard->getField(pos)->goThrough(p);
				}
				
				pos = (pos + 1)%this->myBoard->sizeOfBoard();	
				this->myBoard->getField(pos)->stepOn(p);
				
		}
}
        
void Board::addField(std::shared_ptr<Field> newField)
{
        Fields.push_back(newField);
=======
	
void Board::addField(std::shared_ptr<Field> newField)
{
	Fields.push_back(newField);
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}

int Board::sizeOfBoard() const
{
<<<<<<< HEAD
        return Fields.size();
}

std::shared_ptr< Field > Board::getField(int noOfField)
{
		return this->Fields[noOfField];
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
        
=======
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
	
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}


void Field::stepOn(std::shared_ptr<Player> p){}
void Field::goThrough(std::shared_ptr<Player> p){}
bool Field::permissionToMove(std::shared_ptr<Player> p)
{
<<<<<<< HEAD
        return true;
=======
	return true;
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}
void Field::endOfRound()
{

}
const std::string& Field::getName()
{
<<<<<<< HEAD
        return this->name;
=======
	return this->name;
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}



void Start::stepOn(std::shared_ptr<Player> p)
{
<<<<<<< HEAD
        p->giveCash(startPrice);
}
void Start::goThrough(std::shared_ptr<Player> p)
{
        Start::stepOn(p);
=======
	p->giveCash(startPrice);
}
void Start::goThrough(std::shared_ptr<Player> p)
{
	Start::stepOn(p);
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}


void Reward::stepOn(std::shared_ptr< Player > p)
{
<<<<<<< HEAD
        p->giveCash(this->reward);
=======
	p->giveCash(this->reward);
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}


void Punishment::stepOn(std::shared_ptr< Player > p)
{
<<<<<<< HEAD
        //TODO rzucic wyjatek jesli p->takeCash(this->punishmentPrice) < punishmentPrice (to znaczy ze zbankrutowal)
        p->takeCash(this->punishmentPrice);
=======
	//TODO rzucic wyjatek jesli p->takeCash(this->punishmentPrice) < punishmentPrice (to znaczy ze zbankrutowal)
	p->takeCash(this->punishmentPrice);
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}


void Deposit::goThrough(std::shared_ptr< Player > p)
{
<<<<<<< HEAD
        //TODO to samo co wyzej
        cash += p->giveCash(this->payPrice);
}
void Deposit::stepOn(std::shared_ptr< Player > p)
{
        p->giveCash(this->cash);
        cash = 0;
=======
	//TODO to samo co wyzej
	cash += p->giveCash(this->payPrice);
}
void Deposit::stepOn(std::shared_ptr< Player > p)
{
	p->giveCash(this->cash);
	cash = 0;
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}

void Aquarium::stepOn(std::shared_ptr< Player > p)
{
<<<<<<< HEAD
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
=======
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
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}

void Property::stepOn(std::shared_ptr< Player > p)
{
<<<<<<< HEAD
        //TODO WYJATKIIIII
        this->Owner->takeCash(p->giveCash(this->priceOfStay));
=======
	//TODO WYJATKIIIII
	this->Owner->takeCash(p->giveCash(this->priceOfStay));
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}

bool Property::noOwner()
{
<<<<<<< HEAD
        if (this->Owner)
                return true;
        return false;
=======
	if (this->Owner)
		return true;
	return false;
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}


int Player::getPos()
{
<<<<<<< HEAD
        return this->position;
=======
	return this->position;
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}

void Player::takeCash(int _cash)
{
<<<<<<< HEAD
        this->cash += _cash;
=======
	this->cash += _cash;
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}

int Player::getCash()
{
<<<<<<< HEAD
        return this->cash;
=======
	return this->cash;
>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65
}

int Player::giveCash(int _cash)
{
<<<<<<< HEAD
        auto it = this->myProperties.begin();
//         while ((this->cash < _cash) && (it != this->myProperties.end()))
//         {
//                 if(this->wantSell(it.))
//         }
}
=======
	auto it = this->myProperties.begin();
// 	while ((this->cash < _cash) && (it != this->myProperties.end()))
// 	{
// 		if(this->wantSell(it.))
// 	}
}




>>>>>>> fdacda4a99e47254a1eadaa8db4980bebcab2d65

#include "mojagrubaryba.h"

MojaGrubaRyba::MojaGrubaRyba()
{

}


void MojaGrubaRyba::play(unsigned int rounds)
{
		unsigned int counter = 0;
		try{
				while((++counter <= rounds))
				{
					makeRound();
				}
		}catch(EndOfGameException& e)
		{
			
		}
}

void MojaGrubaRyba::makeRound() throw(EndOfGameException)
{
		for(auto it = Players.begin(); it != Players.end(); )
		{
			try
			{
					if(Players.size() > 1)
					{
							makeMove(*it);
							it++;
						
					}else
					{
						throw EndOfGameException();
					}
			}
			catch(PlayerBankruptException& e)
			{
					bankruptPlayer(*it);
					it = Players.erase(it);
			}
		}
}


void MojaGrubaRyba::makeMove(std::shared_ptr<Player> p) throw(PlayerBankruptException)
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

void MojaGrubaRyba::bankruptPlayer(std::shared_ptr< Player > p)
{
		auto it = Players.begin();
		while (*it != p)
		{
				it++;
				if (it == Players.end())
				{
					int dupa = 666;
					throw dupa;
				}
		}
		it = Players.erase(it);
		
}

       
void Board::addField(std::shared_ptr<Field> newField)
{
        Fields.push_back(newField);
}

int Board::sizeOfBoard() const
{
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

std::string Field::getName()
{
        return this->name;
}



void Start::stepOn(std::shared_ptr<Player> p)
{
        p->takeCash(startPrice);
}
void Start::goThrough(std::shared_ptr<Player> p)
{
        Start::stepOn(p);
}


void Reward::stepOn(std::shared_ptr< Player > p)
{
        p->takeCash(this->reward);
}


void Punishment::stepOn(std::shared_ptr< Player > p) throw(PlayerBankruptException)
{
        //TODO rzucic wyjatek jesli p->takeCash(this->punishmentPrice) < punishmentPrice (to znaczy ze zbankrutowal)
        int cashGiven = 0;
        p->giveCash(this->punishmentPrice);
		if(cashGiven < punishmentPrice) throw PlayerBankruptException();
}


void Deposit::goThrough(std::shared_ptr< Player > p) throw(PlayerBankruptException)
{
        //TODO to samo co wyzej
        auto pair = p->giveCash(this->payPrice);
        
		if(pair.second) throw PlayerBankruptException();
}
void Deposit::stepOn(std::shared_ptr< Player > p)
{
        p->takeCash(this->cash);
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

void Property::stepOn(std::shared_ptr< Player > p) throw(PlayerBankruptException)
{
        //TODO WYJATKIIIII
        auto pair =  p->giveCash(this->priceOfStay);
        this->Owner->takeCash(pair.first);
		if(pair.second) throw PlayerBankruptException();
}

bool Property::noOwner()
{
        if (this->Owner)
                return true;
        return false;
}

void Property::getSold()
{
		this->Owner.reset();
}

int Property::getPrice()
{
		return this->price;
}

//PLAYER

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



std::pair<int, bool> Player::giveCash(int _cash) 
{
		bool bankrupt = false;
        auto it = myProperties.begin();
        while ((this->cash < _cash) && (it != this->myProperties.end()))
        {
                if(this->wantSell((*it)->getName()))
				{
					this->cash += ((*it)->getPrice())/2;
					(*it)->getSold();
					it = myProperties.erase(it);//TODO niedokonczone
				}else
				{
					it++;
				}
		}
		if (cash < _cash) //znaczy ze zbankrutowal
		{
				bankrupt = true;
				it = myProperties.begin();
				while(it != myProperties.end())
				{
						cash += (*it)->getPrice()/2;
						(*it)->getSold();
				}
				
		}
		cash = cash >= _cash? _cash: cash;
		return std::make_pair(cash, bankrupt);
}

//HUMAN PLAYER; //FIXME
//HumanPlayer::HumanPlayer(Human _h) : h(_h), position(0), cash(1000), myProperties()  {};


HumanPlayer::HumanPlayer(std::string _name, std::shared_ptr< Human > _h):Player(name),h(_h)
{

}


std::shared_ptr< HumanPlayer > HumanPlayer::create(std::string _name, std::shared_ptr< Human > _h)
{
	return std::shared_ptr<HumanPlayer>(new HumanPlayer(_name, h));	
}


// std::shared_ptr<HumanPlayer> HumanPlayer::create(Human& _h)
// {
// 	return std::shared_ptr<Human>(_h);
// }
//teraz glupie funkcje;

/*
std::string const& HumanPlayer::getName(){
	return h->getName();
}*/


bool HumanPlayer::wantBuy(std::string const& propertyName){
	return h->wantBuy(propertyName);
}

bool HumanPlayer::wantSell(std::string const& propertyName){
	return h->wantSell(propertyName);
}

// std::shared_ptr<HumanPlayer> HumanPlayer::clone(){
// 	return HumanPlayer(*this);
// }


//COMPUTER PLAYER; //FIXME ZROBIC TO DOBRZE;
/*
ComputerPlayer::ComputerPlayer(std::string _name) : Player(_name), myProperties() {};*/
/*
std::shared_ptr<ComputerPlayer> ComputerPlayer::create(std::string _name){
	return std::shared_ptr<ComputerPlayer>(new ComputerPlayer(_name));
}*/


/*
std::string const& ComputerPlayer::getName(){
	return name;
}*/


//DUMBCOMPUTERPLAYER;
DumbComputerPlayer::DumbComputerPlayer(std::string _name) : ComputerPlayer(_name){};

std::shared_ptr<ComputerPlayer> DumbComputerPlayer::create(std::string _name){
	return std::shared_ptr<ComputerPlayer>(new DumbComputerPlayer(_name));
}
//FIXME sprawdzic czy pierwsze kupuje;
bool DumbComputerPlayer::wantBuy(std::string const& propertyName){
	return (++buyOffers%3 == 0);
}
bool DumbComputerPlayer::wantSell(std::string const& propertyName){
	return false;
}

//SMARTASSCOMPUTERPLAYER
SmartassComputerPlayer::SmartassComputerPlayer(std::string _name) : ComputerPlayer(_name){};

std::shared_ptr<ComputerPlayer> SmartassComputerPlayer::create(std::string _name){
	return std::shared_ptr<ComputerPlayer>(new SmartassComputerPlayer(_name));
}
bool SmartassComputerPlayer::wantBuy(std::string const& propertyName){
	return true;
}
bool SmartassComputerPlayer::wantSell(std::string const& propertyName){
	return false;
}

//FACTORY;

std::shared_ptr< ComputerPlayer > ConcretePlayerFactory::createComputerPlayer(ComputerLvl lvl, std::string name)
{
		if (lvl == ComputerLvl::DUMB) 
			return std::shared_ptr< ComputerPlayer >(new DumbComputerPlayer(name));
		else
			return std::shared_ptr< ComputerPlayer >(new SmartassComputerPlayer(name));
			
}

void ConcretePlayerFactory::registerComputerPlayer( GrubaRyba::ComputerLevel l, std::shared_ptr<ComputerPlayer> p ){
	computerPlayerMap.insert(std::pair<GrubaRyba::ComputerLevel, std::shared_ptr<ComputerPlayer> >(l,p));
}

std::string Player::getName()
{
	return this->name;
}

std::shared_ptr< ComputerPlayer > ComputerPlayer::create(std::string _name)
{

}

ConcretePlayerFactory::ConcretePlayerFactory()
{
	
}


void MojaGrubaRyba::addComputerPlayer(GrubaRyba::ComputerLevel level)
{

}
void MojaGrubaRyba::addHumanPlayer(std::shared_ptr< Human > human)
{

}
MojaGrubaRyba::MojaGrubaRyba(std::shared_ptr< PlayerFactory > _factory, std::shared_ptr< HumanPlayerPrototype > _humanPlayerPrototype)
{

}
void MojaGrubaRyba::setDie(std::shared_ptr< Die > die)
{

}



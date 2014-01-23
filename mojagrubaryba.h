#ifndef MOJAGRUBARYBA_H
#define MOJAGRUBARYBA_H

#include<vector>
#include<string>
#include<memory>
#include<map>
#include"grubaryba.h"

typedef GrubaRyba::ComputerLevel ComputerLvl;

//TODO UKRYC STALE W KONSTRUKTORACH
const int priceOfAnemonia = 160;
const int priceOfAporina = 220;
const int priceOfGrota = 300;
const int priceOfMenella = 280;
const int priceOfStatek = 250;
const int priceOfPennatula = 400;

const int aquaWait = 3;
const int priceOfPayLaguna = 15;
const int priceOfPayRekin = 180;
const int rewardBlazenki = 120;

const int startPrice = 50;

class Player;
class Field;
class Board;
class ComputerPlayer;
class HumanPlayer;
class ComputerStrategy;

class MojaGrubaRyba //public GrubaRyba
{
public:
        MojaGrubaRyba();
	MojaGrubaRyba(std::shared_ptr<PlayerFactory> _factory, std::shared_ptr<HumanPlayerPrototype> _humanPlayerPrototype);
	//TODO zmienic powyzszy konstruktor zeby bral w argumencie liczbe graczy;
private:

        std::vector<std::shared_ptr<Player>> Players;
        std::shared_ptr<Board> myBoard;

	std::shared_ptr<PlayerFactory> factory;
	std::shared_ptr<Player> humanPlayerPrototype;

        void makeRound();
        void makeMove(std::shared_ptr<Player> p);
	void bankruptPlayer(std::shared_ptr<Player> p);
};


class Board
{

public:
	Board(){}
	void addField(std::shared_ptr<Field> newField);
	int sizeOfBoard() const;
protected:
        std::vector<std::shared_ptr<Field>> Fields;
};

class MGRBoard: public Board
{
public:
	MGRBoard();
};

class Field
{
public:
        //puste funkcje (nic nie robią)
        Field(const std::string& _name):
				name(_name){}
        void stepOn(std::shared_ptr<Player> p);
        void goThrough(std::shared_ptr<Player> p);
        bool permissionToMove(std::shared_ptr<Player> p);
	void endOfRound();
	const std::string& getName();
		
protected:
	const std::string name;
};



class Start: public Field
{
public:
        Start(const std::string& _name):
				Field(_name){}
        void stepOn(std::shared_ptr<Player> p);
        void goThrough(std::shared_ptr<Player> p);
};

class Reward: public Field
{
public:
        Reward(const std::string& _name, int price):
		Field(_name),
		reward(price){}
        void stepOn(std::shared_ptr<Player> p);
private:
        int reward;
};

class Punishment: public Field
{
public:
        Punishment(const std::string& _name, int price):
		Field(_name),
                punishmentPrice(price){}
        void stepOn(std::shared_ptr<Player> p);
protected:
        int punishmentPrice;
};
class Deposit: public Field
{
        
public:
	Deposit(const std::string& _name, int _payPrice):
		Field(name),
                cash(0),
                payPrice(_payPrice){}
        void stepOn(std::shared_ptr<Player> p);
        void goThrough(std::shared_ptr<Player> p);
private:
        int cash;
	int payPrice;
};
class Aquarium: public Field
{
public:
        Aquarium(const std::string& _name, int wait):
				Field(name),
                waitTime(wait){}
	
	void stepOn(std::shared_ptr<Player> p);
        bool permissionToMove(std::shared_ptr<Player> p);
	void endOfRound();
private:
        int waitTime;
        std::map<std::shared_ptr<Player>, int> waitingPlayers;
};

class Property: public Field
{
public:
	Property(const std::string& _name, int _price, int _priceOfStay):
		Field(_name),
		price(_price),
		priceOfStay(_priceOfStay){}
        void stepOn(std::shared_ptr<Player> p);
	bool noOwner();

protected:
        std::shared_ptr<Player> Owner;
	int price;
	int priceOfStay;
};



class Coral: public Property
{
public:
		Coral(const std::string& _name, int _price):
				Property(_name, _price,_price*percentOfStay/100)
				{}
			
private:
		const int percentOfStay = 20;
};

class PublicProperty: public Property
{
public:
		PublicProperty(const std::string& _name, int _price):
				Property(_name, _price, _price*percentOfStay/100){};
		
private:
		const int percentOfStay = 40;
	
};

//======================================================================================= 
//TO CO NOWE TO PONIZEJ.
//
//



//Klasa Player Jest Klasą Bazowa dla ComputerPlayer oraz dla HumanPlayer.
//TODO: zastanowic sie czy klasa nie powinna czegos implementowac

class Player{
public:
        
        // Zwraca imię człowieka.
        virtual std::string const& getName() const = 0;

        // Zwraca true, jeśli człowiek chce kupić daną posiadłość.
        virtual bool wantBuy(std::string const& propertyName) = 0;

        // Zwraca true, jeśli człowiek chce sprzedać daną posiadłość.
        // Wywoływane w przypadku, gdy brakuje człowiekowi pieniędzy na zakup lub opłaty.
        virtual bool wantSell(std::string const& propertyName) = 0;

        
        virtual int getPos() = 0;
	virtual void takeCash(int _cash) = 0;
	virtual int giveCash(int _cash) = 0; //zwraca min(_cash, cash - _cash) czyli tyle na ile go stac
	
	//TODO Zastanowic sie raz jeszcze nad tymi metodami, ale na 99% nie.
	//ich implementacja znajdzie sie w graczu.
	//virtual shared_ptr<Player> clone() const = 0;
	//virtual shared_ptr<Player> create() const = 0;
	//virtual ~Player() = 0;

	//TODO zastanowic sie czy klasa nie powinna czegos implementowac.
	//int getCash();
//private:
	//std::string name;
	//int number;

        //int position;
	//int cash;
	//std::vector<std::shared_ptr<Property>> myProperties;
};

//class HumanPlayerPrototype, to Prototyp -- pomoze latwo zmienic implementacje klasy Human;
//Zmiana Human --> piszemy class NewHumanPlayer: public Player, public HumanPlayerPrototype{...}
//Przekazujemy obiket nowoutowrzonej klasy w parametrze konstruktora MojejGrubejRyby;
// UWAGA : implementacja addHumanPlayer(h) uzywa czegos takiego: prototype.create(h);
class HumanPlayerPrototype{
	virtual shared_ptr<HumanPlayerPrototype> create(Human _h) ;
	//virtual shared_ptr<HumanPlayerPrototype> clone();
};

// klasa HumanPlayer jest ADAPTEREM.
// umie odpowiadac na komunkaty klasy MojaGrubaRyba korzystajac z klasy Human;
class HumanPlayer: public Player, public HumanPlayerPrototype{
public:
        HumanPlayer(std::shared_ptr<Human> _h); //: human(h){};
	shared_ptr<HumanPlayer> create(std::shared_ptr<Human> _h);
private:
	std::shared_ptr<Human> h;
	
	int position;
	int cash;
	std::vector<std::shared_ptr<Property> > myProperties;
};

class ComputerPlayer: public Player{
public:
	//TODO rostrzygnac czy potrzebne.
        //ComputerPlayer(GrubaRyba::ComputerLevel level):myLevel(level){}
	
	
	virtual shared_ptr<Player> create(std::string name);
	//shared_ptr<ComputerPlayer> clone();
private:
	std::string name;
	int position;
	int cash;
	std::vector<std::shared_ptr<Property> > myProperties;

        //GrubaRyba::ComputerLevel myLevel;
};

class PlayerFactory {
	public:
		virtual void registerComputerPlayer( ComputerLvl lvl, shared_ptr<ComputerPlayer> prototype ) = 0;
		virtual shared_ptr<ComputerPlayer> createComputerPlayer( ComputerLvl lvl, std::string name ) = 0;
};

class ConcretePlayerFactory : public PlayerFactory{
	private:
		std::map<typename GrubaRyba::ComputerLevel, ComputerPlayer> computerPlayerMap;
	public:
		void registerComputerPlayer( ComputerLvl lvl, shared_ptr<ComputerPlayer> prototype);
		shared_ptr<ComputerPlayer> createComputerPlayer( ComputerLvl lvl, std::string name );
};



#endif

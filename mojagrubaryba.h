#ifndef MOJAGRUBARYBA_H
#define MOJAGRUBARYBA_H

#include<vector>
#include<string>
#include<cstring>
#include<memory>
#include<map>
#include<exception>
#include<tuple>
#include<iostream>
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
class HumanPlayerPrototype;
class HumanPlaceHolder;
class PlayerFactory;
class MGRBoard;

class PlayerBankruptException: public std::exception
{
	
};

class EndOfGameException: public std::exception
{
	
};


class MojaGrubaRyba : public GrubaRyba
{
friend class MGRBoard;

public:
        MojaGrubaRyba();
	MojaGrubaRyba(std::shared_ptr<PlayerFactory> _factory, std::shared_ptr<HumanPlayerPrototype> _humanPlayerPrototype);
	//TODO zmienic powyzszy konstruktor zeby bral w argumencie liczbe graczy;
		
        void setDie(std::shared_ptr<Die> die);

		void addComputerPlayer(GrubaRyba::ComputerLevel level);
		void addHumanPlayer(std::shared_ptr<Human> human);
		void play(unsigned int rounds);
private:

        std::vector<std::shared_ptr<Player>> Players;

		std::shared_ptr<PlayerFactory> factory;
		std::shared_ptr<HumanPlayer> humanPlayerPrototype;
		std::shared_ptr<MGRBoard> myBoard;
        void makeRound() throw (EndOfGameException);
        void makeMove(std::shared_ptr<Player> p) throw(PlayerBankruptException);
        void bankruptPlayer(std::shared_ptr<Player> p);
		std::shared_ptr<Die> defaultDie;
		void addPlayer(std::shared_ptr<Player> p);
		std::map<std::shared_ptr<Player>, bool> bankruptPlayers;
		int playingPlayers;
		int roundNo;
};


class Board
{

public:
        Board(){}
        void addField(std::shared_ptr<Field> newField);
        int sizeOfBoard() const;
		std::shared_ptr<Field> getField(int noOfField);
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
        virtual void stepOn(std::shared_ptr<Player> p);
        virtual void goThrough(std::shared_ptr<Player> p);
        virtual bool permissionToMove(std::shared_ptr<Player> p);
        virtual void endOfRound();
        std::string getName();
		virtual void writeStatus(std::shared_ptr<Player> p);
                
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
        void stepOn(std::shared_ptr<Player> p) throw(PlayerBankruptException);
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
        void goThrough(std::shared_ptr<Player> p) throw(PlayerBankruptException);
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
		void writeStatus(std::shared_ptr<Player> p);
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
        void stepOn(std::shared_ptr<Player> p) throw(PlayerBankruptException);
        bool noOwner();
		int getPrice();
		void getSold();

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

//Klasa Player Jest Klasą Bazowa dla ComputerPlayer oraz dla HumanPlayer.
//TODO: zastanowic sie czy klasa nie powinna czegos implementowac

class Player{
public:
        
	Player(std::string _name, int _position = 0, int _cash = 1000):
	name(_name),
	position(_position),
	cash(_cash){}
	
	//virtual ~Player() = 0;
        // Zwraca imię człowieka.
        std::string getName();

        // Zwraca true, jeśli człowiek chce kupić daną posiadłość.
        virtual bool wantBuy(std::string const& propertyName) = 0;

        // Zwraca true, jeśli człowiek chce sprzedać daną posiadłość.
        // Wywoływane w przypadku, gdy brakuje człowiekowi pieniędzy na zakup lub opłaty.
        virtual bool wantSell(std::string const& propertyName) = 0;

        
        int getPos();
        void takeCash(int _cash);
        std::pair<int, bool> giveCash(int _cash); //zwraca min(_cash, cash - _cash) czyli tyle na ile go stac
								//i bool czy zbankrutowal
        int getCash();
        
protected:
	
		std::string name;
        int position;
        int cash;
        std::vector<std::shared_ptr<Property>> myProperties;
};

//class HumanPlayerPrototype, to Prototyp -- pomoze latwo zmienic implementacje klasy Human;
//Zmiana Human --> piszemy class NewHumanPlayer: public Player, public HumanPlayerPrototype{...}
//Przekazujemy obiket nowoutowrzonej klasy w parametrze konstruktora MojejGrubejRyby;
// UWAGA : implementacja addHumanPlayer(h) uzywa czegos takiego: prototype.create(h);
class HumanPlayerPrototype{
	virtual std::shared_ptr<HumanPlayer> create(std::string _name, std::shared_ptr<Human> _h) = 0;
	//virtual shared_ptr<HumanPlayerPrototype> clone();
};

// klasa HumanPlayer jest ADAPTEREM.
// umie odpowiadac na komunkaty klasy MojaGrubaRyba korzystajac z klasy Human;
class HumanPlayer: public Player, public HumanPlayerPrototype {
public:
        HumanPlayer (std::string _name, std::shared_ptr<Human> _h ); //: human(h){};

	std::shared_ptr<HumanPlayer> create(std::string _name, std::shared_ptr<Human> _h);
	
        bool wantBuy(std::string const& propertyName);

        bool wantSell(std::string const& propertyName);
private:
	std::shared_ptr<Human> h;
};

class HumanPlaceHolder : public Human{
    std::string const& getName(){
	    return "placeholder";
    }

    bool wantBuy(std::string const& propertyName){
	    return false;
    }

    bool wantSell(std::string const& propertyName) {
	    return false;
    }

    virtual std::shared_ptr<Human> clone(){
	    return std::shared_ptr<Human>(new HumanPlaceHolder());
    }

};

class ComputerPlayer: public Player{
public:
	//TODO rostrzygnac czy potrzebne.
        //ComputerPlayer(GrubaRyba::ComputerLevel level):myLevel(level){}
	

	
	virtual std::shared_ptr<ComputerPlayer> create(std::string _name) = 0;
	ComputerPlayer(std::string _name) : Player(_name){}
	//std::shared_ptr<ComputerPlayer> create(std::string _name);
private:
	//GrubaRyba::ComputerLevel myLevel;
};

class DumbComputerPlayer : public ComputerPlayer {

	private :
		int buyOffers;
		int selOffers;
	public:
		DumbComputerPlayer(std::string _name);
		std::shared_ptr<ComputerPlayer> create (std::string _name);
		bool wantBuy(std::string const& propertyName);
		bool wantSell(std::string const& propertyName);
};

class SmartassComputerPlayer : public ComputerPlayer {

	public:
		SmartassComputerPlayer(std::string _name);
		std::shared_ptr<ComputerPlayer> create (std::string _name);
		bool wantBuy(std::string const& propertyName);
		bool wantSell(std::string const& propertyName);
};

//FACTORY
class PlayerFactory {
	public:
		//virtual ~PlayerFactory() = 0;
		virtual void registerComputerPlayer( ComputerLvl lvl, std::shared_ptr<ComputerPlayer> prototype ) = 0;
		virtual std::shared_ptr<ComputerPlayer> createComputerPlayer( ComputerLvl lvl, std::string name ) = 0;
};

class ConcretePlayerFactory : public PlayerFactory
{
public:
		ConcretePlayerFactory();
		void registerComputerPlayer( ComputerLvl lvl, std::shared_ptr<ComputerPlayer> prototype);
		std::shared_ptr<ComputerPlayer> createComputerPlayer( ComputerLvl lvl, std::string name );

		
		//~ConcretePlayerFactory();	
private:
		std::map<ComputerLvl, std::shared_ptr<ComputerPlayer> > computerPlayerMap;
	
};



#endif

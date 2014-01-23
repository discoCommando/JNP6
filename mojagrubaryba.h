#ifndef MOJAGRUBARYBA_H
#define MOJAGRUBARYBA_H

#include<vector>
#include<string>
#include<memory>
#include<map>
#include<exception>
#include<tuple>
#include"grubaryba.h"


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
class MGRBoard;

class PlayerBankruptException: public std::exception
{
	
};

class EndOfGameException: public std::exception
{
	
};


class MojaGrubaRyba //public GrubaRyba
{
friend class MGRBoard;

public:
		
        MojaGrubaRyba(); virtual void setDie(std::shared_ptr<Die> die) = 0;

		void addComputerPlayer(GrubaRyba::ComputerLevel level);
		void addHumanPlayer(std::shared_ptr<Human> human);
		void play(unsigned int rounds);
private:
        std::vector<std::shared_ptr<Player>> Players;
        std::shared_ptr<MGRBoard> myBoard;
        void makeRound() throw (EndOfGameException);
        void makeMove(std::shared_ptr<Player> p) throw(PlayerBankruptException);
        void bankruptPlayer(std::shared_ptr<Player> p);
		std::shared_ptr<Die> defaultDie;
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
        void stepOn(std::shared_ptr<Player> p);
        void goThrough(std::shared_ptr<Player> p);
        bool permissionToMove(std::shared_ptr<Player> p);
        void endOfRound();
        std::string getName();
                
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

class Player
{
public:
        
        // Zwraca imię człowieka.
        virtual std::string const& getName() const = 0;

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
        int position;
        int cash;
        std::vector<std::shared_ptr<Property>> myProperties;
};

class HumanPlayer: public Player
{
public:
        HumanPlayer(Human& h) :
                human(h){}
                
private:
        Human& human;
};

class ComputerPlayer: public Player
{
public:
        ComputerPlayer(GrubaRyba::ComputerLevel level):
                myLevel(level){}private:
        
        GrubaRyba::ComputerLevel myLevel;
        std::shared_ptr<ComputerStrategy> strategy;

};

// Strategia decyzji kup/ sprzedaj;
class ComputerStrategy {
        public:
                //TODO ASK: virtualny destruktor??
                virtual ~ComputerStrategy(){};

                virtual bool wantBuy() = 0;
                virtual bool wantSell() = 0;
};

class DumbComputerStrategy : public ComputerStrategy {

        private :
                int buyOfferCount;
                int sellOfferCount;
        public :
                DumbComputerStrategy();
                bool wantBuy(); 
                bool wantSell();
};

class SmartassComputerStrategy : public ComputerStrategy {

        public :
                SmartassComputerStrategy();
                bool wantBuy(); 
                bool wantSell();
};



#endif
#ifndef MOJAGRUBARYBA_H
#define MOJAGRUBARYBA_H

#include<vector>
#include<string>
#include<memory>
#include<map>
#include"grubaryba.h"

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
private:
        std::vector<std::shared_ptr<Player>> Players;
        std::shared_ptr<Board> myBoard;
        void makeRound();
        void makeMove(std::shared_ptr<Player> p);
};

class Board
{
protected:
        std::vector<std::shared_ptr<Field>> Fields;
};

class MGRBoard
{
public:
		MGRBoard();
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
        
private:
        int position;
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
        Reward(int price,const std::string& _name):
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
        Deposit(const std::string& _name):
				Field(name),
                cash(0){}
public:
        void stepOn(std::shared_ptr<Player> p);
        void goThrough(std::shared_ptr<Player> p);
private:
        int cash;
};
class Aquarium: public Field
{
public:
        Aquarium(const std::string& _name, int wait):
				Field(name),
                waitTime(wait){}
        bool permissionToMove(std::shared_ptr<Player> p);
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
        virtual void stepOn(std::shared_ptr<Player> p);
protected:
        std::shared_ptr<Player> Owner;
		int price;
		int priceOfStay;
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
                myLevel(level){}
        
private:
        
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

class Coral: public Property
{
public:
		Coral(int _price, const std::string& _name):
				Property(_name, _price,_price*percentOfStay/100)
				{}
			
private:
		const int percentOfStay = 20;
};

class PublicProperty: public Property
{
public:
		PublicProperty(int _price, const std::string& _name):
				Property(_name, _price, _price*percentOfStay/100){};
		
private:
		const int percentOfStay = 40;
	
};

#endif
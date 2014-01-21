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
private:
	std::vector<Field> Fields;
};

class Field
{
public:
	//puste funkcje (nic nie robią)
	void stepOn(std::shared_ptr<Player> p);
	void goThrough(std::shared_ptr<Player> p);
	bool permissionToMove(std::shared_ptr<Player> p);
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

class Start: public Field
{
	Start();
public:
	void stepOn(std::shared_ptr<Player> p);
	void goThrough(std::shared_ptr<Player> p);
};

class Reward: public Field
{
public:
	Reward(int price):
		reward(price){}
	void stepOn(std::shared_ptr<Player> p);
private:
	int reward;
};

class Punishment: public Field
{
public:
	Punishment(int price):
		punishmentPrice(price){}
	void stepOn(std::shared_ptr<Player> p);
private:
	int punishmentPrice;
};
class Deposit: public Field
{
	Deposit():
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
	Aquarium(int wait):
		waitTime(wait){}
	bool permissionToMove(std::shared_ptr<Player> p);
private:
	int waitTime;
	std::map<std::shared_ptr<Player>, int> waitingPlayers;
};
class Property: public Field
{
public:
	virtual void stepOn(std::shared_ptr<Player> p);
private:
	std::shared_ptr<Player> Owner;
	int priceOfStay;
};

class HumanPlayer: public Player
{
public:
	HumanPlayer(Human& h):
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

};

class ComputerStrategy
{
	
};

#endif

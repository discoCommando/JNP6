#ifndef GRUBARYBA_H
#define GRUBARYBA_H

#include<vector>
#include<string>
#include"grubaryba.h"

class Player;
class Field;
class Board;
class ComputerPlayer;
class HumanPlayer;

class MojaGrubaRyba //public GrubaRyba
{
private:
	std::vector<Player> Players;
	Board myBoard;
	void makeRound();
	void makeMove(Player p);
};

class Board
{
	std::vector<Field> Fields;
};

class Field
{
public:
	//puste funkcje (nic nie robią)
	void stepOn(Player p);
	void goThrough(Player p);
	bool permissionToMove(Player p);
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
};

class Start: public Field
{
	void stepOn(Player p);
	void goThrough(Player p);
};
class Reward: public Field
{
	void stepOn(Player p);
};
class Punishment: public Field
{
	void stepOn(Player p);
};
class Deposit: public Field
{
	void stepOn(Player p);
	void goThrough(Player p);	
};
class Aquarium: public Field
{
	void goThrough(Player p);
	bool permissionToMove(Player p);
};
class Property: public Field
{
	virtual void stepOn(Player p);
};

#endif

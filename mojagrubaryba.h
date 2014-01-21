#ifndef GRUBARYBA_H
#define GRUBARYBA_H

#include<vector>
#include"grubaryba.h"

class Player;
class Field;
class Board;
class ComputerPlayer;
class HumanPlayer;

class MojaGrubaRyba: public GrubaRyba
{
private:
	Players: std::vector<player>;
	Board myBoard;
	void makeRound();
	void makeMove(Player p);
};

class Board
{
	Fields: std::vector<Field>;
};

class Field
{
public:
	virtual void stepOn(Player p);
	virtual void goThrough(Player p);
	virtual bool permissionToMove(Player p);
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

#endif

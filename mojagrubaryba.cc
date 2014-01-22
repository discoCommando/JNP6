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
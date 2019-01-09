#include "Energizer.h"
#include "StageScreen.h"
//#include "Ball.h"

//check if the nemo above the energizer
bool Energizer::pushNemo(StageScreen & stage) const
{
	sf::Vector2f position{ m_sprite.getPosition().x ,m_sprite.getPosition().y - SIZE_SQUARE.second };
	if (stage.positionOfTheNemo(position))
	{
		stage.setSuccessStage();
		return true;
	}
	return false;
}

bool Energizer::pushObject(StageScreen & stage) 
{
	//sf::Vector2f position{ m_sprite.getPosition().x, m_sprite.getPosition().y - SIZE_SQUARE.second };
	//passiveIterator itPassive = stage.checkPositionPassive(position);//return pointer to the player on this place if doesn't have player return nullptr
	//if (!stage.iteratorToEndPassive(itPassive))
	//{
	//	//if (typeid(itPassive) == typeid(Ball))//check if this player it's pointer to dwarf
	//	//{
	//		m_numOfBalls-=1;
	//		stage.setTypeAnimate(BALL_INSERT_ANIMATE);
	//		stage.deletePassive(itPassive);
	//		return true;
	//		//stage.displayAnimate()
	//	//}
	//}
	return false;
}

#include "Rock.h"
#include "StageScreen.h"
#include "ActiveObject.h"
#include <conio.h>  
#include <thread>
#include "NoExploding.h"

//=======================================================================
bool Rock::movement(StageScreen& stage)
{
	sf::Vector2f oldPos = m_sprite.getPosition();
	m_sprite.move(m_direction.x*SIZE_SQUARE.first, m_direction.y*SIZE_SQUARE.second);
	std::shared_ptr<Rock>b = std::make_shared<Rock>(*this);
	std::string s1 = typeid(*b).name();
	std::string s2 = typeid(*this).name();
	if (!stage.controlCollide(b))
	{
		m_sprite.setPosition(oldPos);
		return false;
	}
	//m_sprite.move(m_direction.x*SIZE_SQUARE.first, m_direction.y*SIZE_SQUARE.second);
	return true;
}



#include <memory>
#include <thread>
#include <conio.h>
#include <iostream>
#include "Crab.h"
#include "PassiveObject.h"
#include "StageScreen.h"
#include "Moveable.h"
#include "Utilities.h"
#include "NoExploding.h"

Crab::Crab(const sf::Vector2f & position) :ActiveObject(position, *Singleton<sf::Texture>::getInstance()->getResource("crab"))
{
	m_directionTime = StageScreen::getClock().getElapsedTime();
}
bool Crab::movement(StageScreen& stage)
{
	m_direction = getDirectionCrab(stage);
//	m_direction = D_UP;
	m_sprite.move(m_direction*m_speed);
	std::shared_ptr<Crab> c=std::make_shared<Crab>(*this);
	if (StageScreen::getClock().getElapsedTime() - m_directionTime >= sf::milliseconds(500))
	{
		if (StageScreen::getClock().getElapsedTime() - m_directionTime >= sf::milliseconds(1000))
		{
			m_direction = getRandomDirection();
			m_directionTime = StageScreen::getClock().getElapsedTime();
		}
		else
			m_direction = getDirectionCrab(stage);
	}
	return true;
}


sf::Vector2f Crab::getDirectionCrab(StageScreen&stage)
{
	float minDist = 1000;
	Direction minDir = getDirectionFromVector(getRandomDirection());
	float len = m_sprite.getGlobalBounds().width;
	sf::Vector2f pos;
	for (int i = 0; i < 4; ++i)
	{
		pos = m_sprite.getPosition() + getVectorDirection((Direction)i)*len;
		if (stage.isValidPosition(pos))
		{
			if (getDistanceBetween(stage.getNemoPosition(), pos) < minDist)
			{
				minDist = getDistanceBetween(stage.getNemoPosition(), pos);
				minDir = (Direction)i;
			}
		}
	}
	return getVectorDirection(minDir);
}
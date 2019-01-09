#include "Ball.h"
#include "StageScreen.h"
#include "ActiveObject.h"
#include "NoExploding.h"

//=======================================================================
bool Ball::movement(StageScreen& stage)
{
	sf::Vector2f oldPos = m_sprite.getPosition();
	m_sprite.move(m_direction.x*SIZE_SQUARE.first, m_direction.y*SIZE_SQUARE.second);
	std::shared_ptr<Ball >b = std::make_shared<Ball>(*this);
	if (!stage.controlCollide(b))
	{
		m_sprite.setPosition(oldPos);
		return false;
	}
	//m_sprite.move(m_direction.x*SIZE_SQUARE.first, m_direction.y*SIZE_SQUARE.second);
	return true;
}
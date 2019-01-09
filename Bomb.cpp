#include "Bomb.h"
#include "StageScreen.h"
#include "ActiveObject.h"
#include "NoExploding.h"

//=======================================================================
bool Bomb::movement(StageScreen& stage)
{
	sf::Vector2f oldPos = m_sprite.getPosition();
	m_sprite.move(m_direction.x*SIZE_SQUARE.first, m_direction.y*SIZE_SQUARE.second);
	std::shared_ptr<Bomb>b = std::make_shared<Bomb>(*this);
	if (!stage.controlCollide(b))
	{
		m_sprite.setPosition(oldPos);
		return false;
	}
	return true;
}

#include "Moveable.h"
#include "Utilities.h"
#include "StageScreen.h"
Moveable::Moveable(const sf::Vector2f& position, const sf::Texture& texture) :
	Object(position, texture),m_speed(startSpeed) {}

//bool Moveable::collide(Object& object, StageScreen& stage)
//{
//	return object.collide(*this, stage);
//}
// Change how the texture look
void Moveable::setRotation()
{
	if (m_direction == D_RIGHT)
	{
		//m_sprite.setScale({ 1, 1 });
		//m_sprite.setRotation(0);
	}
	else if (m_direction == D_DOWN)
	{
		//m_sprite.setScale({ 1, 1 });
		//m_sprite.setRotation(90);
	}
	else if (m_direction == D_LEFT)
	{
		//m_sprite.setScale({ -1, 1 });
		//m_sprite.setRotation(0);
	}
	else if (m_direction == D_UP)
	{
		//m_sprite.setScale({ -1, 1 });
		//m_sprite.setRotation(90);
	}
}
sf::Vector2f Moveable::getRandomDirection() const
{
	int r = rand() % 4;
	switch (r)
	{
	case 0: // LEFT
		return D_LEFT;
	case 1: // RIGHT
		return D_RIGHT;
	case 2: // DOWN
		return D_DOWN;
	case 3: // UP
		return D_UP;
	}
}
// Check if a position is out of game bounds, and if it is go to the other side.
sf::Vector2f Moveable::getOutBounds(sf::Vector2f old)
{
	float width = m_sprite.getLocalBounds().width / 2;
	float height = m_sprite.getLocalBounds().height / 2;

	if (old.x < 0)
		old.x = SIZE_WINDOW.second- width;
	if (old.x + width > SIZE_WINDOW.second)
		old.x = 0;
	if (old.y < 0)
		old.y = SIZE_WINDOW.first - height;
	if (old.y + height > SIZE_WINDOW.first)
		old.y = 0;

	return old;
}


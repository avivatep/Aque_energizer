#pragma once
#include "Object.h"
//lass Ball;
//lass Energizer;
//class Nemo;
//#include "StageScreen.h"
class StageScreen;
const float startSpeed =10;
class Moveable : public Object
{
public:
	Moveable(const sf::Vector2f&, const sf::Texture&);
	virtual bool movement( StageScreen&) = 0;
	void setDirection(sf::Vector2f direction){ m_direction = direction; setRotation();}
	void setOldPosition() { m_oldPosition = (m_sprite.getPosition()); }
	const sf::Vector2f& getOldPosition() { return m_oldPosition; }
	const sf::Vector2f& getDirection() { return m_direction; }
	void setRotation();
	virtual ~Moveable() = default;
protected:
	sf::Vector2f getRandomDirection() const;
	sf::Vector2f getOutBounds(sf::Vector2f old);
	sf::Vector2f m_direction;
	sf::Vector2f m_oldPosition;
	float m_speed;
};
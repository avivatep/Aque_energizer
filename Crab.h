#pragma once
#include "ActiveObject.h"
#include <sfml/Graphics.hpp>
#include "SingeltonSource.h"

class Crab : public ActiveObject
{
public:
	Crab(const sf::Vector2f&position);
	virtual bool movement(StageScreen&);
	sf::Vector2f getDirectionCrab(StageScreen&stage);
	virtual ~Crab() = default;
private:
	sf::Time m_directionTime;
	float m_speed = 4;
};

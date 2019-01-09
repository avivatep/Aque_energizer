#pragma once
#include "Moveable.h"
class StageScreen;
class PassiveObject : public Moveable
{
public:
	PassiveObject(const sf::Vector2f&position, const sf::Texture&texture) :Moveable(position, texture) {}
	virtual bool movement(StageScreen&) = 0;
	//virtual bool checkCollision(StageScreen&)=0;
	virtual ~PassiveObject() = default;
};


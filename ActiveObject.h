#pragma once
#include "Moveable.h"

class ActiveObject :public Moveable
{
public:
	ActiveObject(const sf::Vector2f& position, const sf::Texture& texture):
		Moveable(position, texture) {}
	virtual bool movement(StageScreen&) = 0;
	virtual ~ActiveObject() = default;
};



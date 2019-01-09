#pragma once
#include "Object.h"
class StaticObject:public Object
{
public:
	StaticObject(const sf::Vector2f&position, const sf::Texture&texture );
	virtual ~StaticObject() = default;
};


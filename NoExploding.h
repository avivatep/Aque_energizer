#pragma once
#include "StaticObject.h"
#include "SingeltonSource.h"
class NoExploding :public StaticObject
{
public:
	NoExploding(const sf::Vector2f&position, const sf::Texture&texture) :StaticObject(position,texture) {}
	virtual ~NoExploding() = default;
};
//======================Wall=================================
class Wall :public NoExploding
{
public:
	Wall(const sf::Vector2f&position) 
		:NoExploding(position, *Singleton<sf::Texture>::getInstance()->getResource("wall")){}
	virtual ~Wall() = default;
};
//===========================================================
class Space :public NoExploding
{
public:
	Space(const sf::Vector2f& position) :NoExploding(position, *Singleton<sf::Texture>::getInstance()->getResource("space")){}
	virtual ~Space() = default;
};

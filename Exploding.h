#pragma once
#include "StaticObject.h"
#include "SingeltonSource.h"
class Exploding:public StaticObject
{
public:
	Exploding(const sf::Vector2f&position, const sf::Texture&texture) :StaticObject(position,texture) {}
	virtual ~Exploding() = default;
};

//===============================================
class Door : public Exploding
{
public:
	Door(const sf::Vector2f&position) :Exploding(position, *Singleton<sf::Texture>::getInstance()->getResource("door")) {}
	virtual ~Door() = default;
};

//====================Dirt===========================
class Dirt : public Exploding
{
public:
	Dirt(const sf::Vector2f&position) :Exploding(position, *Singleton<sf::Texture>::getInstance()->getResource("dirt")) {}
	virtual ~Dirt() = default;
};

//===============================================
class Ground : public Exploding
{
public:
	Ground(const sf::Vector2f&position) :Exploding(position, *Singleton<sf::Texture>::getInstance()->getResource("ground")) {}
	virtual ~Ground() = default;
};

//===============================================
class Key : public Exploding
{
public:
	Key(const sf::Vector2f&position) :Exploding(position, *Singleton<sf::Texture>::getInstance()->getResource("key")) {}
	virtual ~Key() = default;
};
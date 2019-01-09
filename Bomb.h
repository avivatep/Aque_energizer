#pragma once
#include "PassiveObject.h"
#include "ActiveObject.h"
#include "SingeltonSource.h"
class Bomb :public PassiveObject
{
public:
	Bomb(const sf::Vector2f& position) : PassiveObject(position, *Singleton<sf::Texture>::getInstance()->getResource("bomb")) {}
	virtual bool movement(StageScreen& stage);
	virtual ~Bomb() = default;
};



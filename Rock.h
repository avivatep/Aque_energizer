#pragma once
#include "PassiveObject.h"
#include "ActiveObject.h"
#include "SingeltonSource.h"

class Rock :public PassiveObject
{
public:
	Rock(const sf::Vector2f& position) : PassiveObject(position, *Singleton<sf::Texture>::getInstance()->getResource("rock")) {}
	virtual bool movement(StageScreen& stage);
	virtual ~Rock() = default;
};



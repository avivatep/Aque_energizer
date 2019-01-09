#pragma once
#include "PassiveObject.h"
#include "ActiveObject.h"
#include "SingeltonSource.h"
class Ball:public PassiveObject
{
public:
	Ball(const sf::Vector2f& position) : PassiveObject(position, *Singleton<sf::Texture>::getInstance()->getResource("ball")) {}
	virtual bool movement(StageScreen& stage);
	virtual ~Ball() = default;
};


#pragma once
#include "Nemo.h"
#include "PassiveObject.h"
#include <memory>
#include "StageScreen.h"
#include "SingeltonSource.h"
#include <iostream>
unsigned Nemo::m_lives = 4;
bool Nemo::movement(StageScreen& stage)
{
	m_oldPosition = m_sprite.getPosition();
	m_sprite.move(m_direction.x*SIZE_SQUARE.first, m_direction.y*SIZE_SQUARE.second);
	return true;
}

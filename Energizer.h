#pragma once
#include "NoExploding.h"
class StageScreen;
class Energizer:public NoExploding
{
public:
	Energizer(const sf::Vector2f&position):  NoExploding(position, *Singleton<sf::Texture>::getInstance()->getResource("energizer")){}
	virtual ~Energizer() = default;
	void addBall(unsigned int num) { m_totalBall=num; }
	void subBall() { m_numOfBalls++; }
	unsigned getTotalBall() { return m_totalBall; }
	unsigned getnumOfBalls(){return m_numOfBalls;}
	bool fullEnergy(){ return m_numOfBalls == m_totalBall; }
	bool pushNemo(StageScreen& stage)const;
	bool pushObject(StageScreen& stage);
private:
	unsigned  m_numOfBalls = 0;
	unsigned  m_totalBall =0;
};


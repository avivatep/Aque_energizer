#pragma once
#include "ActiveObject.h"
#include "SingeltonSource.h"
class StageScreen;

class Nemo :public ActiveObject
{
public:
	Nemo(const sf::Vector2f&position) :ActiveObject(position, *Singleton<sf::Texture>::getInstance()->getResource("nemo")) {}
	bool movement(StageScreen&);
	void setLocation(const sf::Vector2f&newLocation) { m_sprite.setPosition(newLocation); }
	bool getIsDead() { return m_isDead; }
	void isDead() { m_lives--; m_isDead = true; }
	void setLives(unsigned live) { m_lives = live; }
	unsigned getNUmLives() { return m_lives; }
	virtual ~Nemo() = default;
private:
	static unsigned m_lives;
	bool m_isDead = false;
};

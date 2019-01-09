#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "DataEndScreen.h"
#include "SingeltonSource.h"
class Help : public Screen
{
public:
	Help() :Screen(*Singleton<sf::Texture>::getInstance()->getResource("background")) {}
	void playAnimation(sf::RenderWindow&, sf::Sprite, sf::Texture, sf::IntRect&, sf::Sprite, int, int& count);
	virtual typeOfScreen controlScreen(sf::RenderWindow&);
	virtual void draw(sf::RenderWindow&)const {}
	virtual typeOfScreen handleEvent(sf::RenderWindow&);
	~Help() {}
private:
	int m_numScreen = 1;
	//sf::Clock m_clock;
};
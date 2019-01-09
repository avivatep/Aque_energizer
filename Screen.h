#pragma once
 #include <SFML/Graphics.hpp>
class DataEndScreen;
//#include <SFML/Audio.hpp>
enum typeOfScreen { MENU, STAGE,HELP, EXIT };
class Screen
{
public:
	Screen(const sf::Texture& texture) 
	 {
		setBackGround(texture);
	}
	virtual typeOfScreen controlScreen(sf::RenderWindow&) = 0;
	virtual void draw(sf::RenderWindow&)const = 0;
	void setBackGround(const sf::Texture& texture) {
	m_backGround.setTexture(texture);
	m_backGround.setPosition(0, 0);
	m_backGround.scale(1.78f, 1.8f);
	}
	virtual typeOfScreen handleEvent(sf::RenderWindow&) = 0;
	~Screen() = default;
protected:
	//====================proprties window===============================
	sf::Sprite m_backGround;
};


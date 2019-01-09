#pragma once
#include <unordered_map>
#include <string>
#include <memory>


#include "Screen.h"
#include "SingeltonSource.h"
class DataEndScreen;
typedef std::pair<typeOfScreen, sf::Sprite> option;
typedef std::unordered_map <typeOfScreen, sf::Sprite>unMapOfoption;

class MenuScreen:public Screen
{
public:
	MenuScreen();
	void draw(sf::RenderWindow& window)const;
	typeOfScreen controlScreen(sf::RenderWindow&);
	virtual typeOfScreen handleEvent(sf::RenderWindow&) ;
	void initializeCommandUnMap();
	~MenuScreen()=default;
private:
unMapOfoption  m_option;
};


#include "MenuScreen.h"
#include "StageScreen.h"
#include "DataEndScreen.h"
#include <algorithm>

MenuScreen::MenuScreen() :Screen(*Singleton<sf::Texture>::getInstance()->getResource("backgroundMenu"))
{
	initializeCommandUnMap();
}

void MenuScreen::draw(sf::RenderWindow & window) const
{
	window.draw(m_backGround);
	std::for_each(m_option.begin(), m_option.end(), [&window](option option) {window.draw(option.second); });
}

typeOfScreen MenuScreen::controlScreen(sf::RenderWindow &window)
{
	static typeOfScreen nextScreen;
	SingeltonSound::instance()->playBackgroundMusic();
	while (window.isOpen())
	{
		nextScreen = handleEvent(window);
		if (nextScreen != MENU)
		{
			SingeltonSound::instance()->stopAllSounds();
			return nextScreen;
		}
		window.clear();
		draw(window);
		window.display();
	}	
	SingeltonSound::instance()->stopAllSounds();
	return nextScreen;
}
typeOfScreen MenuScreen::handleEvent(sf::RenderWindow &window)
{
	unMapOfoption::const_iterator clickedOn;

	for (sf::Event event; window.pollEvent(event); )
	{
		if ((event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
		{
			window.close();
		}
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
		{
			auto mouseClick = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			clickedOn = std::find_if(m_option.begin(), m_option.end(),
				[mouseClick](std::pair<typeOfScreen, sf::Sprite> p) { return ((p).second.getGlobalBounds().contains(mouseClick)); });
			if (clickedOn == m_option.end())
				break;
			else
				return clickedOn->first;
		}
		}
	}
	return  MENU;
}
void MenuScreen::initializeCommandUnMap()
{
	sf::Sprite newGame(*Singleton<sf::Texture>::getInstance()->getResource("newGame"));
	sf::Sprite help(*Singleton<sf::Texture>::getInstance()->getResource("help"));
	sf::Sprite quit(*Singleton<sf::Texture>::getInstance()->getResource("quit"));

	newGame.setPosition(620, 250);
	help.setPosition(690, 350);
	quit.setPosition(700, 450);

	m_option.emplace(STAGE, newGame);
	m_option.emplace(HELP, help);
	m_option.emplace(EXIT, quit);
}

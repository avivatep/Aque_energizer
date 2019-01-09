#include <thread>
#include <conio.h>
#include "Controller.h"
#include "StageScreen.h"
#include "SingeltonSource.h"
#include "DataEndScreen.h"
#include "MenuScreen.h"
#include "Help.h"
#include "SingeltonSound.h"

//-----------------------Controller----------------------------
Controller::Controller()
{
	m_screen.emplace_back(std::make_shared<MenuScreen>());//menu window
	m_screen.emplace_back(std::make_shared<StageScreen>());//game window
	m_screen.emplace_back(std::make_shared<Help>());//help window
}
//--------------------------run----------------------------
void Controller::run()
{
	typeOfScreen nextScreen;
	sf::RenderWindow window(sf::VideoMode(SIZE_WINDOW.second, SIZE_WINDOW.first), "AQUA ENERGIZER");//, sf::Style::Resize||sf::Style::Close);
	m_runWindow = m_screen[MENU];
	while (window.isOpen())
	{
		nextScreen = m_runWindow->controlScreen(window);
		if (nextScreen == EXIT)
		{
			SingeltonSound::instance()->playGoodbye();
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			window.close();
		}
		else
			m_runWindow = m_screen[nextScreen];
	}
}
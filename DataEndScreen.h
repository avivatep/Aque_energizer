#pragma once
#include "Screen.h"
#include "DataEndScreen.h"
#include "SingeltonSource.h"
#include "SingeltonSound.h"
#include "StageScreen.h"
class DataEndScreen:public Screen
{
public:
	DataEndScreen(long totalScore, unsigned timeBonus, statusNemo status):
		Screen(*Singleton<sf::Texture>::getInstance()->getResource("gameOver")),
		m_totalScore(totalScore), m_timeBonus(timeBonus),m_status(status){
		if (status == succesStage)
			setBackGround(*Singleton<sf::Texture>::getInstance()->getResource("levelCompleted1"));
		else
		{
			SingeltonSound::instance()->playGameOver();
			setBackGround(*Singleton<sf::Texture>::getInstance()->getResource("gameOver"));
		}
	}
	virtual typeOfScreen controlScreen(sf::RenderWindow&window)
	{
		typeOfScreen nextScreen = MENU ;
		while (window.isOpen()&&nextScreen!=STAGE)
		{
			nextScreen = handleEvent(window);
			window.clear();
			draw(window);
			window.display();
		}
		return STAGE;
	}
	virtual void draw(sf::RenderWindow&window)const
	{
		static sf::Text message1, message2;
		message1.setPosition(550, 480);
		message1.setFont(*Singleton<sf::Font>::getInstance()->getResource("arial"));
		message1.setString(std::to_string(m_timeBonus));
		message2.setPosition(550, 515);
		message2.setFont(*Singleton<sf::Font>::getInstance()->getResource("arial"));
		message2.setString(std::to_string(m_totalScore));
		window.draw(m_backGround);
		if (m_status == succesStage)
		{
			window.draw(message1);
			window.draw(message2);
		}
	}
	virtual typeOfScreen handleEvent(sf::RenderWindow&window)
	{
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
				return STAGE;
			}
			default:break;
			}
		}
	}
	~DataEndScreen() = default;
private:
	typeOfScreen m_nextScreen;
	statusNemo m_status;
	long m_totalScore;
	unsigned m_timeBonus;
};


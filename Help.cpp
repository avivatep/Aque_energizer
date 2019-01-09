#include "Help.h"
#include "Screen.h"
#include "StageScreen.h"

#include <thread>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

sf::Clock hclock;
typeOfScreen Help::controlScreen(sf::RenderWindow& window)
{
	sf::Texture help1(*Singleton<sf::Texture>::getInstance()->getResource("help1"));
	sf::Texture help2(*Singleton<sf::Texture>::getInstance()->getResource("help2"));
	sf::Texture help3(*Singleton<sf::Texture>::getInstance()->getResource("help3"));
	sf::Texture help4(*Singleton<sf::Texture>::getInstance()->getResource("help5"));
	sf::Texture help5(*Singleton<sf::Texture>::getInstance()->getResource("help6"));

	sf::Sprite shelp1(help1);
	sf::Sprite shelp2(help2);
	sf::Sprite shelp3(help3);
	sf::Sprite shelp4(help4);
	sf::Sprite shelp5(help5);

	shelp1.scale(0.85, 0.75);
	shelp2.scale(1.24, 1.1);
	shelp3.scale(1.24, 1.1);
	shelp4.scale(1.19, 1.1);
	shelp5.scale(1.19, 1.1);

	sf::Texture animation1(*Singleton<sf::Texture>::getInstance()->getResource("animation1"));
	sf::IntRect rectSourceSprite1(0, 0, animation1.getSize().x / 4, animation1.getSize().y);
	sf::Sprite sanimation1(animation1, rectSourceSprite1);
	sanimation1.scale(0.76, 0.6);
	sanimation1.setPosition(670, 170);
	sanimation1.setTextureRect(rectSourceSprite1);

	sf::Texture animation2(*Singleton<sf::Texture>::getInstance()->getResource("animation2"));
	sf::IntRect rectSourceSprite2(0, 0, animation2.getSize().x / 5, animation2.getSize().y);
	sf::Sprite sanimation2(animation2, rectSourceSprite2);
	sanimation2.scale(0.76, 0.62);
	sanimation2.setPosition(675, 170);
	sanimation2.setTextureRect(rectSourceSprite2);

	sf::Texture animation3(*Singleton<sf::Texture>::getInstance()->getResource("animation3"));
	sf::IntRect rectSourceSprite3(0, 0, animation3.getSize().x / 6, animation3.getSize().y);
	sf::Sprite sanimation3(animation3, rectSourceSprite3);
	sanimation3.scale(0.76, 0.62);
	sanimation3.setPosition(675, 170);
	sanimation3.setTextureRect(rectSourceSprite3);

	sf::Texture animation4(*Singleton<sf::Texture>::getInstance()->getResource("animation4"));
	sf::IntRect rectSourceSprite4(0, 0, animation4.getSize().x / 3, animation4.getSize().y);
	sf::Sprite sanimation4(animation4, rectSourceSprite4);
	sanimation4.scale(0.76, 0.62);
	sanimation4.setPosition(670, 177);
	sanimation4.setTextureRect(rectSourceSprite4);

	sf::Texture animation5(*Singleton<sf::Texture>::getInstance()->getResource("animation5"));
	sf::IntRect rectSourceSprite5(0, 0, animation5.getSize().x / 5, animation5.getSize().y);
	sf::Sprite sanimation5(animation5, rectSourceSprite5);
	sanimation5.scale(0.76, 0.62);
	sanimation5.setPosition(667, 177);
	sanimation5.setTextureRect(rectSourceSprite5);

	int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;
	SingeltonSound::instance()->playInstuctionsSound();
	while (window.isOpen())
	{
		if (handleEvent(window) == HELP)
		{
			switch (m_numScreen)
			{
			case 1:
				playAnimation(window, sanimation1, animation1, rectSourceSprite1, shelp1, 4, count1); break;
			case 2:
				playAnimation(window, sanimation2, animation2, rectSourceSprite2, shelp2, 5, count2); break;
			case 3:
				playAnimation(window, sanimation3, animation3, rectSourceSprite3, shelp3, 6, count3); break;
			case 4:
				playAnimation(window, sanimation4, animation4, rectSourceSprite4, shelp4, 3, count4); break;
			case 5:
				playAnimation(window, sanimation5, animation5, rectSourceSprite5, shelp5, 5, count5); break;
			default:
				break;
			}
		}
		else
		{
			SingeltonSound::instance()->stopAllSounds();
			return  MENU;
		}
	}
	return  HELP;
}

void Help::playAnimation(sf::RenderWindow& window, sf::Sprite sanimation, sf::Texture animation, sf::IntRect& rectSourceSprite, sf::Sprite help, int numPicAnimate, int& count)
{
	if (hclock.getElapsedTime().asSeconds() > 0.2)
	{
		if (count == numPicAnimate)
		{
			count = 0;
			rectSourceSprite.left = 0;
		}
		rectSourceSprite.left += animation.getSize().x / numPicAnimate;
		sanimation.setTextureRect(rectSourceSprite);
		count++;
		hclock.restart();
	}
	window.clear();
	window.draw(help);
	window.draw(sanimation);
	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(300));	// sleep for to see the ball 
}

typeOfScreen Help::handleEvent(sf::RenderWindow & window)
{
	sf::Vector2f movement;
	for (sf::Event event; window.pollEvent(event); )
	{
		if ((event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
		{
			return  MENU;
		}
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
		{
			auto mouseClick = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			sf::RectangleShape rect(sf::Vector2f{ 184.f, 1224.f });
			rect.setPosition(sf::Vector2f{ 58,580 });
			window.draw(rect);
			if (rect.getGlobalBounds().contains(mouseClick))
				return  MENU;
			break;
		}
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				m_numScreen >= 2 ? m_numScreen-- : m_numScreen = 1; break;
			case sf::Keyboard::Right:
				m_numScreen < 5 ? m_numScreen++ : m_numScreen = 5; break;
			case sf::Keyboard::Escape:
				return  MENU;
			default:
				break;
			}
		}
		default:
			break;
		}
	}
	return HELP
		;
}


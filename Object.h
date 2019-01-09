#pragma once
#include <SFML/Graphics.hpp>
//#include "Crab.h"
const std::pair<float, float> SIZE_SQUARE{ 60,60};
class Object
{
public:
	/*Constructors*/
	Object(const sf::Vector2f&position, const sf::Texture&texture);
	//default constructer
   /*get and set functions*/
	void setTexture(const sf::Texture&texture) { m_sprite.setTexture(texture); }
	void setLocation(const sf::Vector2f& newPosition) { m_sprite.setPosition(newPosition); }
	const sf::Vector2f& getLocation()const { return m_sprite.getPosition(); }//return the location of this sprite
	 /*temporary functions*/
	void draw(sf::RenderWindow &window) const { window.draw(m_sprite); }//draw the square	
	sf::Sprite getSprite() { return m_sprite; }
	//check if the user clicked in the range of the square by rectangle blocks
	bool checkWithin(const sf::Vector2f& clicked) const { return(m_sprite.getGlobalBounds().contains(clicked)); }
	virtual ~Object() = default;
	bool checkC(sf::FloatRect& f) const
	{
	return 	(m_sprite.getGlobalBounds().intersects(f));
	}
	 //Checks if one object contains the other
	bool checkCollision(Object &obj) const
	{
		sf::FloatRect rect1(m_sprite.getGlobalBounds());
		sf::FloatRect rect2(obj.m_sprite.getGlobalBounds());
		bool b= (m_sprite.getGlobalBounds().intersects(obj.m_sprite.getGlobalBounds()));
		return b;
	}
	//virtual bool collide(Object& object, StageScreen& stage) = 0;
	/*virtual bool collide(Ball& ball, StageScreen& stage) = 0;
	virtual bool collide(Nemo& nemo, StageScreen& stage) = 0;
	virtual bool collide(Crab& crab, StageScreen& stage) = 0;*/
protected:
	sf::Sprite m_sprite;
};


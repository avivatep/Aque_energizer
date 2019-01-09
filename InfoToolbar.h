#pragma once
#include <SFML/Graphics.hpp>


template<typename T>
class InfoToolbar {
public:
	InfoToolbar(const sf::Sprite&, const sf::Vector2f& location, const sf::Font& font, T info);
	virtual ~InfoToolbar()  = 0;

	void display(sf::RenderWindow& window);
	virtual const sf::Text& getText() = 0;
	virtual void setInfo(T) = 0;
	T getInfo() const { return m_info; }

protected:
	sf::Sprite m_display;
	sf::Text m_text;
	T m_info;         //time or number of moves

};
//=======================================================================
//                     string of game class
//=======================================================================
class StringInfo : public InfoToolbar<std::string>
{
public:
	StringInfo(const sf::Sprite& display, const sf::Vector2f&, const sf::Font&,std::string&);
	~StringInfo() {}
	void setInfo(std::string str)override { m_info = str; }
	const sf::Text& getText() override;
	
};
//
//=======================================================================
//                     score class
//=======================================================================
class ScoreInfo : public InfoToolbar<unsigned>
{
public:
	ScoreInfo(const sf::Sprite&, const sf::Vector2f&, const sf::Font&, unsigned);
	~ScoreInfo() {}
	void setInfo(unsigned add)override { m_info += add; }
	const sf::Text& getText() override;
};
//=======================================================================
//                     time of game class
//=======================================================================
class TimeInfo : public InfoToolbar<float>
{
public:
	TimeInfo(const sf::Sprite& display, const sf::Vector2f&, const sf::Font&, float);
	~TimeInfo() {}
	void setInfo(float time)override { m_info -= time; }
	const sf::Text& getText() override;
	bool didLose()const { return  m_info > 0.f; }
};
//========================================================


////==============================================================================
////             information class
////==============================================================================
template<typename T>
inline InfoToolbar<T>::InfoToolbar(const sf::Sprite& display, const sf::Vector2f& location, const sf::Font& font, T info)
	: m_display(display), m_info(info) {
	m_display.setPosition(location);
	m_text.setFont(font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::White);
}

//------------------------------------------------------------------
template<typename T>
inline void InfoToolbar<T>::display(sf::RenderWindow& window) {
	window.draw(m_display);
	window.draw(getText());
}

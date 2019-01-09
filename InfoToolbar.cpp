#include "InfoToolbar.h"
#include <string>
//
//=======================================================================
//                    Score class
//=======================================================================
ScoreInfo::ScoreInfo(const sf::Sprite& display, const sf::Vector2f& location, const sf::Font& font, unsigned info)
	:InfoToolbar<unsigned>(display, location, font, info) {
	m_text.setCharacterSize(30);
	m_text.setPosition(sf::Vector2f{ location.x + 30,location.y + 25 });

}
//--------------------------------------------------------------------
const  sf::Text& ScoreInfo::getText() {
	m_text.setString(std::to_string(int(m_info)));
	return m_text;
}
//-------------------------------------------------------------------


//=======================================================================
//                     time of game class
//=======================================================================
TimeInfo::TimeInfo(const sf::Sprite& display, const sf::Vector2f& location, const sf::Font& font, float info)
	:InfoToolbar<float>(display, location, font, info) {
	m_text.setCharacterSize(25);
	m_text.setPosition(sf::Vector2f{ location.x + 20,location.y + 25 });
}
//--------------------------------------------------------------------------
const sf::Text& TimeInfo::getText() {
	if (m_info > .6f &&  m_info < 1.f)
		m_info -= .4f;
	auto str = std::to_string(m_info);
	m_text.setString(std::string{ '0',str[0],':',str[2],str[3] });

	return m_text;
}
////==============================================================================
template<typename T>
InfoToolbar<T>::~InfoToolbar() = default;

StringInfo::StringInfo(const sf::Sprite & display, const sf::Vector2f &location, const sf::Font &font, std::string& info)
:InfoToolbar<std::string>(display, location, font, info) {}

const sf::Text & StringInfo::getText()
{
	return m_text;
}

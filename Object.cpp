#include "Object.h"


Object::Object(const sf::Vector2f&position, const sf::Texture&texture) :m_sprite(texture)
{
	
	m_sprite.scale((float)SIZE_SQUARE.first /(float) texture.getSize().x, (float)SIZE_SQUARE.second / (float)texture.getSize().y);
//	m_sprite.setOrigin(sf::Vector2f{ SIZE_SQUARE.first / 2,SIZE_SQUARE.second / 2 });
	m_sprite.setPosition(position);
}


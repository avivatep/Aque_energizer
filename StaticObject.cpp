#include "StaticObject.h"
#include "StageScreen.h"

StaticObject::StaticObject(const sf::Vector2f&position, const sf::Texture&texture) :Object(position, texture) {}
//
//bool StaticObject::collide(Object & object, StageScreen & stage)
//{
//	return object.collide(*this, stage);
//}
//
//bool StaticObject::collide(Ball & ball, StageScreen & stage)
//{
//	return m_type == STATIC_SPACE;
//}
//
//bool StaticObject::collide(Nemo & nemo, StageScreen & stage)
//{
//	return m_type == STATIC_SPACE;
//}

//bool StaticObject::collide(Crab & crab, StageScreen & stage)
//{
//	switch (m_type)
//	{
//	case STATIC_SPACE: break;
//	case STATIC_KEY:
//	case STATIC_DIRT:
//	case STATIC_ENERGIZER: return false;
//		break;
//	default: return false;
//	}
//	return false;
//}

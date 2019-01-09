#pragma once
#include <sfml/Graphics.hpp>
namespace {
	const sf::Vector2f D_UP = { 0,-1.0 };
	const sf::Vector2f D_DOWN = { 0, 1.0 };
	const sf::Vector2f D_RIGHT = { 1.0, 0 };
	const sf::Vector2f D_LEFT = { -1.0, 0 };
	enum Direction { UP, DOWN, RIGHT, LEFT };
	Direction getDirectionFromVector(const sf::Vector2f& dir)
	{
		if (dir == D_UP)
			return Direction::UP;
		if (dir == D_DOWN)
			return Direction::DOWN;
		if (dir == D_LEFT)
			return Direction::LEFT;
		if (dir == D_RIGHT)
			return Direction::RIGHT;
	}
	sf::Vector2f getVectorDirection(Direction dir)
	{
		switch (dir)
		{
		case Direction::UP:
			return D_UP;
		case Direction::DOWN:
			return D_DOWN;
		case Direction::LEFT:
			return D_LEFT;
		case Direction::RIGHT:
			return D_RIGHT;
		}
	}
	// Calculates the distance between 2 given points
	float getDistanceBetween(sf::Vector2f p1, sf::Vector2f p2)
	{ // d = | x0 – x1 | + | y0 – y1 |
		return std::fabs(p1.x - p2.x) + std::abs(p1.y - p2.y);
	}
	sf::Vector2f getRandomDirection() 
	{
		int r = rand() % 4;
		switch (r)
		{
		case 0: // LEFT
			return D_LEFT;
		case 1: // RIGHT
			return D_RIGHT;
		case 2: // DOWN
			return D_DOWN;
		case 3: // UP
			return D_UP;
		}
	}
	
};
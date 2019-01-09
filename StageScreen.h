#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <list>
#include <SFML/Audio.hpp>
class Energizer;
class Nemo;
class PassiveObject;
class ActiveObject;
#include "StaticObject.h"
#include "InfoToolbar.h"
#include "Screen.h"
#include "ActiveObject.h"
#include "SingeltonSource.h"

using std::list;
using std::unique_ptr;
const std::pair<float, float> SIZE_WINDOW = { 720.f, 1080.f };
const std::pair<unsigned, unsigned> SIZE_BOARD = { 11, 18 };
enum statusNemo{dead,hasLive,play,succesStage};

const int MAX_STAGE = 3;

typedef std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>pairIntersects;
typedef std::pair<pairIntersects, pairIntersects>pairIntersection;
typedef std::list<std::shared_ptr<ActiveObject>>::const_iterator activeIterator;
typedef std::list<std::shared_ptr<PassiveObject>>::const_iterator passiveIterator;
class StageScreen :public Screen
{
public:
	//=================constructor===================================
	StageScreen();
	//====================temp_function===============================
	virtual typeOfScreen controlScreen(sf::RenderWindow&);//controll the stage
	/* return the all object that crash it's him*/
	void clearDataStructure();
	pairIntersection getIntersectObj(std::shared_ptr<Moveable>);
	bool isValidPosition(const sf::Vector2f&)const;
	//set the object in this position to pointer to space
	void setStaticSpace(const sf::Vector2f&);
	//delete the door
	void deleteDoor();
	bool checkCollition(sf::RenderWindow& window);
	//set the success stage
	void setSuccessStage() { m_statusNemo =succesStage;}
	//return the global clock
	static sf::Clock& getClock() { return m_globClock; }
	const sf::Vector2f& getNemoPosition()const;
	//check if the nemo above the energizer
	bool positionOfTheNemo(const sf::Vector2f& position) const;
	//explotion around the position,around the bomb
	void explosion(const sf::Vector2f& position);
	//controoll all collides of the movable
	bool controlCollide(std::shared_ptr<Moveable>moveable);
	//controoll all collides of the movable
	bool controlCrash(std::shared_ptr<Moveable> movable);
	void setScore(unsigned score) { m_currScore += score;
	m_score->setInfo(m_currScore);}
	void drawMessage(sf::RenderWindow& window);
	std::shared_ptr<StaticObject> getStatic(const sf::Vector2f & location) const;
	~StageScreen() = default;
private:

	std::pair<bool, sf::Sprite>m_explosion;//check if need to explotion
	list<std::shared_ptr<ActiveObject>> m_activeObject;  //vector of dynamic objects
	std::vector<std::vector<std::shared_ptr<StaticObject>>> m_statics; //vector of static object
	list<std::shared_ptr<PassiveObject>> m_passives;
	sf::Vector2u m_doorPosition; //the position of the door
	std::shared_ptr<Nemo> m_nemo;
	std::shared_ptr<Energizer> m_energizer;
	std::unique_ptr<InfoToolbar<unsigned>> m_score;
	std::unique_ptr<InfoToolbar<std::string>> m_energy;
	std::unique_ptr<InfoToolbar<float>> m_time;
	std::unique_ptr<InfoToolbar<unsigned>> m_currLevel;
	static unsigned m_level;
	unsigned  m_currScore=0;
	static sf::Clock m_globClock;
	statusNemo m_statusNemo =play;
	sf::Sprite m_backGroundToolbr;
	bool m_fullEnergy = false;
	/*temporary private functions*/
	//=================moving===================================
	//move all the active object
	void moveActive();
	void buildToolBar();
	//handle event
	typeOfScreen handleEvent(sf::RenderWindow&);
	//check if this object it's proximity to the explotion
	bool inIntersectBomb(const sf::Vector2f & position, std::shared_ptr<Object> object);
	void readStage();
	/*return iterator to the active object in this position*/
	activeIterator checkPositionActive(std::shared_ptr<Moveable>)const;
	/*return iterator to the passive object in this position*/
	passiveIterator checkPositionPassive(std::shared_ptr<Moveable>)const;
	//=================draw===================================
	template<class T>
	/* draw the data structure*/
	void draw(sf::RenderWindow& window, const T & vec)const;
	//draw the board
	void drawBoard(sf::RenderWindow& window) const;
	//draw the toolbar
	void drawToolBar(sf::RenderWindow& window)const;
	//draw all the object on the screen
	void draw(sf::RenderWindow& window)const;
};
bool processCollision(std::shared_ptr<Object>, std::shared_ptr<Object>,StageScreen&);
template<typename T>
void StageScreen::draw(sf::RenderWindow& window, const T & vec) const
{
	//std::for_each(vec.begin, vec.end, [&](T tile) {window.draw(tile); });
	for (auto& tile : vec)
		tile->draw(window);
}



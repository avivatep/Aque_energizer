#include <memory>
#include <thread>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "UtilitiesCollide.h"
#include "Utilities.h"
#include "StageScreen.h"
#include "Exploding.h"
#include "NoExploding.h"
#include "PassiveObject.h"
#include "StaticObject.h"
#include "Moveable.h"
#include "Energizer.h"
#include "Nemo.h"
#include "Ball.h"
#include "Bomb.h"
#include "SingeltonSource.h"
#include "Crab.h"
#include "Rock.h"
#include "DataEndScreen.h"
#include "SingeltonSound.h"

#define TIME  0.4f
sf::Clock StageScreen::m_globClock;
unsigned StageScreen::m_level=0;

//=======================constructor===================================
StageScreen::StageScreen() :
	m_backGroundToolbr(*Singleton<sf::Texture>::getInstance()->getResource("toolbar")), Screen(*Singleton<sf::Texture>::getInstance()->getResource("background"))
{
}
//=======================buildToolBar===================================
void StageScreen::buildToolBar()
{
	sf::Texture toolBar = (*Singleton<sf::Texture>::getInstance()->getResource("toolbar"));
	m_backGroundToolbr.setScale(sf::Vector2f(0.54f, 0.7f)); // absolute scale factor
	m_score = std::make_unique<ScoreInfo>(sf::Sprite(*Singleton<sf::Texture>::getInstance()->getResource("space")), sf::Vector2f{ 330,0 }, *Singleton<sf::Font>::getInstance()->getResource("arial"), m_currScore);
	m_time = std::make_unique<TimeInfo>(sf::Sprite(*Singleton<sf::Texture>::getInstance()->getResource("space")), sf::Vector2f{ 760,0 }, *Singleton<sf::Font>::getInstance()->getResource("arial"), TIME*m_level);
	m_currLevel = std::make_unique<ScoreInfo>(sf::Sprite(*Singleton<sf::Texture>::getInstance()->getResource("space")), sf::Vector2f{ 190,0 }, *Singleton<sf::Font>::getInstance()->getResource("arial"), m_level);
	sf::Sprite boom(sf::Sprite(*Singleton<sf::Texture>::getInstance()->getResource("boom")));
	m_explosion = std::make_pair(false, boom);
	m_statusNemo = play;
}
//=======================controlScreen===================================
typeOfScreen StageScreen::controlScreen(sf::RenderWindow&window)
{
	readStage();
	buildToolBar();
	sf::Time deltaTime = m_globClock.getElapsedTime();
	SingeltonSound::instance()->playBackgroundStage();
	while (window.isOpen() && m_statusNemo == play && m_level <= MAX_STAGE)
	{
		if (checkCollition(window))
			if (handleEvent(window) == EXIT)
			{
				SingeltonSound::instance()->stopAllSounds();
				return  MENU;
			}
		m_time->setInfo(m_globClock.restart().asSeconds()*0.01f);
		window.clear();
		draw(window);
		window.display();
		//did lose a time
		if (!(static_cast<TimeInfo*>(m_time.get())->didLose()))
		{
			m_nemo->isDead();
			if (m_nemo->getNUmLives() > 0)
				m_statusNemo = hasLive;
			else
				m_statusNemo = dead;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(35));
		m_nemo->setTexture(*Singleton<sf::Texture>::getInstance()->getResource("nemo"));
		if (m_explosion.first || m_nemo->getIsDead())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));	// sleep for to see the ball 
			m_explosion.first = false;
			if (m_nemo->getIsDead() && m_statusNemo != dead)
				m_statusNemo = hasLive;
		}
	}
	if (m_level > MAX_STAGE)
	{
		SingeltonSound::instance()->stopAllSounds();
		SingeltonSound::instance()->playClapping();
		m_level = 0;
		return MENU;
	}
	/*update the value returned*/
	clearDataStructure();
	drawMessage(window);
	if(m_statusNemo==dead)
		return  MENU;
	return STAGE;
}
//=================readStage===================================
void StageScreen::readStage()
{
	m_level++;
	if (m_level > MAX_STAGE)
		return;
	std::string nameLevel = "level" + std::to_string(m_level) + ".txt";//the name of the level
	std::ifstream level(nameLevel);//open the file
	if (level.eof()) // If no board number was found, return 0'd Board
	{
		level.close();
		return;
	}
	unsigned countBalls = 0;
	m_statics.resize(SIZE_BOARD.first, std::vector<std::shared_ptr<StaticObject>>(SIZE_BOARD.second));  //build the vector
	char object; //the current sign
	for (unsigned i = 0; i < SIZE_BOARD.first; i++)
	{
		for (unsigned j = 0; j < SIZE_BOARD.second; j++)
		{
			do {
				object = level.get();
			} while (object == '\n');//skip on the enters
			sf::Vector2f position(j*SIZE_SQUARE.first, i*SIZE_SQUARE.second + 70);
			switch (object) {
			case 'C': m_activeObject.emplace_back(std::make_shared<Crab>(position)); object = ' '; break; 
			case 'N': m_nemo = (std::make_shared<Nemo>(position)); object = ' '; break; 
			case 'b': m_passives.emplace_back(std::make_shared<Ball>(position)); object = ' '; countBalls++; break; 
			case 'O': m_energizer = (std::make_shared<Energizer>(position));
				     m_statics[i][j] = m_energizer; break;
			case 'r': m_passives.emplace_back(std::make_shared<Rock>(position)); object = ' ';break;
			case 'B': m_passives.emplace_back(std::make_shared<Bomb>(position)); object = ' '; break;
			case '=':m_statics[i][j] = std::make_shared<Wall>(position); break;
			case '#': m_statics[i][j] = std::make_shared<Door>(position);m_doorPosition = {i,j}; break;
			case 'F': m_statics[i][j] = std::make_shared<Key>(position); break;
			case '_': m_statics[i][j] = std::make_shared<Ground>(position); break;
			case 'd': m_statics[i][j] = std::make_shared<Dirt>(position);  break;
			default: object = ' ';
			}
			if (object == ' ')
				m_statics[i][j] = std::make_unique<Space>(position);
		}
	}
	m_energizer->addBall(countBalls);
	m_energy = std::make_unique<StringInfo>(sf::Sprite(*Singleton<sf::Texture>::getInstance()->getResource("space")), sf::Vector2f{ 550,0 }, *Singleton<sf::Font>::getInstance()->getResource("coprgtl"), std::string(std::to_string(m_energizer->getTotalBall()) + "/ " + std::to_string(m_energizer->getnumOfBalls())));
	level.close();
}
//=======================checkPositionActive===================================
activeIterator StageScreen::checkPositionActive(std::shared_ptr<Moveable>moveable) const
{
	activeIterator iterator;
	sf::Vector2f posActiv=moveable->getLocation();
	for (iterator = m_activeObject.begin(); iterator != m_activeObject.end(); ++iterator)
	{
		if (*iterator != moveable && iterator->get()->checkWithin(posActiv))
			return iterator;
	}
	return iterator;
}

//------------------checkPositionPassive-------------------
//passes all the player and check if the mouse click in the bounding rectangle of the player
passiveIterator StageScreen::checkPositionPassive(std::shared_ptr<Moveable>moveable)const
{
	passiveIterator iterator;
	sf::Vector2f posMov = moveable->getLocation();
	for (iterator = m_passives.begin(); iterator != m_passives.end(); ++iterator)
	{
		if (*iterator!=moveable&& iterator->get()->checkWithin(posMov))
			return iterator;
	}
	return iterator;
}

//=================drawMessage===================================
void StageScreen::drawMessage(sf::RenderWindow & window)
{
	SingeltonSound::instance()->stopAllSounds();
	if (m_statusNemo == dead)
	{
		m_level = 0;
		m_nemo->setLives(3);
		DataEndScreen dataEnd(m_currScore, 0, m_statusNemo);
		typeOfScreen type=dataEnd.controlScreen(window);	
	}
	else if (m_statusNemo == hasLive)
	{
		m_level--;
		controlScreen(window);
	}
	else
	{
		DataEndScreen dataEnd(m_currScore, (unsigned int)m_time->getInfo() + m_currScore*2.5, m_statusNemo);
		typeOfScreen type = dataEnd.controlScreen(window);
	}
}

//-------------------getType----------------------
std::shared_ptr<StaticObject> StageScreen::getStatic(const sf::Vector2f & location) const
{
	int i = int((location.y) / SIZE_SQUARE.second);//Calculate the line which is a computer mouse
	int j = int((location.x) / SIZE_SQUARE.first);//Calculating column which is a computer mouse
	return m_statics[i-1][j];
}
//======================clearDataStructure===================================
void StageScreen::clearDataStructure()
{
	std::for_each(m_statics.begin(), m_statics.end(), [&](std::vector<std::shared_ptr<StaticObject> >v)
	{v.clear(); });
	m_activeObject.clear();
	m_passives.clear();
	m_nemo.reset();
	m_energizer.reset();
	m_fullEnergy = false;
}
//========================getIntersectObj===================================
pairIntersection StageScreen::getIntersectObj(std::shared_ptr<Moveable>object)
{
	std::shared_ptr<Object>st1 = nullptr;
	std::shared_ptr<Object>st2 = nullptr;
	std::shared_ptr<Object>st3 = nullptr;
	std::shared_ptr<Object>st4 = nullptr;
	activeIterator iterator;
	bool b = false;
	int count = 0;
	sf::FloatRect &rect1 = (m_nemo)->getSprite().getGlobalBounds();
	if (object->checkC(rect1))
	{
		st1 = m_nemo;
		return pairIntersection{ { st1,st2 },{ st3,st4 } };;
	}
	for (iterator = m_activeObject.begin(); iterator != m_activeObject.end(); ++iterator)
	{
		sf::FloatRect &rect1 = (*iterator)->getSprite().getGlobalBounds();
		if (*iterator != (object) && object->checkC(rect1))
		{
			if (object->checkC(rect1))
			{
				if (count == 0)
					st1 = *iterator;
				else if (count == 1)
					st2 = *iterator;
				else if (count == 2)
					st3 = *iterator;
				else if (count == 3)
				{
					st4 = *iterator;
					break;
				}
				count++;
				b = true;
			}
		}
		if (b)
			return pairIntersection{ { st1,st2 },{ st3,st4 } };
	}


	passiveIterator iteratorPas;
	for (iteratorPas = m_passives.begin(); iteratorPas != m_passives.end(); ++iteratorPas)
	{
		sf::FloatRect &rect1 = (*iteratorPas)->getSprite().getGlobalBounds();
		if (*iteratorPas != (object) && object->checkC(rect1))
		{
			if (object->checkC(rect1))
			{
				if (count == 0)
					st1 = *iterator;
				else if (count == 1)
					st2 = *iterator;
				else if (count == 2)
					st3 = *iterator;
				else if (count == 3)
				{
					st4 = *iterator;
					break;
				}
				count++;
				b = true;
			}

		}
		if (b)
			return pairIntersection{ { st1,st2 },{ st3,st4 } };
	}


	count = 0;
	for (size_t i = 0; i < m_statics.size(); i++)
	{
		for (size_t j = 0; j < m_statics[i].size(); j++)
		{
			sf::FloatRect &rect1 = m_statics[i][j]->getSprite().getGlobalBounds();
			//sf::FloatRect rect2 = tt1.getGlobalBounds();

			if (object->checkC(rect1))
			{
				if (count == 0)
					st1 = m_statics[i][j];
				else if (count == 1)
					st2 = m_statics[i][j];
				else if (count == 2)
					st3 = m_statics[i][j];
				else if (count == 3)
				{
					st4 = m_statics[i][j];
					break;
				}
				count++;
			}
		}
	}
	return pairIntersection{ { st1,st2 },{ st3,st4 } };
}
//


//=================isValidPosition===================================
bool StageScreen::isValidPosition(const sf::Vector2f & location) const
{
	sf::RectangleShape rect(sf::Vector2f(SIZE_WINDOW.second, SIZE_WINDOW.first));
	rect.setPosition({ 0, 0 });
	return (rect.getGlobalBounds().contains(location));
}
//=====================processCollision===================================
bool processCollision(std::shared_ptr<Object> object1, std::shared_ptr<Object> object2, StageScreen&stage)
{
	HitFunctionPtr phf = lookup(typeid(*object1).name(),
		typeid(*object2).name());
	if (phf)
		return phf(object1, object2, (stage));
	else
		return false;
}

//-------------------setSpace----------------------
void StageScreen::setStaticSpace(const sf::Vector2f & location)
{
	int i = int((location.y) / SIZE_SQUARE.second);//Calculate the line which is a computer mouse
	int j = int((location.x) / SIZE_SQUARE.first);//Calculating column which is a computer mouse
	m_statics[i - 1][j]=move(std::make_shared<Space>(location));
}
//=================handleEvent===================================
typeOfScreen StageScreen::handleEvent(sf::RenderWindow & window)
{
	sf::Vector2f movement;
	bool isArrow = true;
	for (sf::Event event; window.pollEvent(event); )
	{
		if ((event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
		{
			return MENU;
		}
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
		{
			auto mouseClick = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			sf::RectangleShape rect(sf::Vector2f{ 46.f, 37.f });
			rect.setPosition(sf::Vector2f{ 1018,26 });
			window.draw(rect);
			if (rect.getGlobalBounds().contains(mouseClick))
			{
				SingeltonSound::instance()->playExplosion();
				m_nemo->isDead();
				if (m_nemo->getNUmLives() == 0)
					m_statusNemo = dead;
				else
				  m_statusNemo = hasLive;

			}
			break;
		}
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				m_nemo->setDirection(D_LEFT);
				m_nemo->setTexture(*Singleton<sf::Texture>::getInstance()->getResource("nemoLeft")); break;
			case sf::Keyboard::Right:
				m_nemo->setDirection(D_RIGHT);
				m_nemo->setTexture(*Singleton<sf::Texture>::getInstance()->getResource("nemoRight")); break;
			case sf::Keyboard::Up:
				m_nemo->setDirection(D_UP);
				m_nemo->setTexture(*Singleton<sf::Texture>::getInstance()->getResource("Nemo_down")); break;
			case sf::Keyboard::Down:
				m_nemo->setDirection(D_DOWN);
				m_nemo->setTexture(*Singleton<sf::Texture>::getInstance()->getResource("Nemo_down")); break;
			default: isArrow = false;  break;
			}
			if (isArrow)
			{
				m_nemo->movement(*this);
				if (!controlCollide(m_nemo))
				{
					m_nemo->setTexture(*Singleton<sf::Texture>::getInstance()->getResource("nemo"));
					m_nemo->setLocation(m_nemo->getOldPosition());
				}
				else
					SingeltonSound::instance()->playNemoGo();
				break;
			}
		}
		break;
		}
		break;
	}
	moveActive();
	return STAGE;
}
//------------------draw-----------------------
void StageScreen::drawBoard(sf::RenderWindow& window) const
{
	std::for_each(m_statics.begin(), m_statics.end(), 
	[&](std::vector<std::shared_ptr<StaticObject>>lineStatic) {draw(window, lineStatic); });
	draw(window, m_activeObject);
	draw(window, m_passives);
	drawToolBar(window);
	m_nemo->draw(window);
    m_energizer->draw(window);
}
//=================deleteDoor===================================
void StageScreen::deleteDoor()
{
	m_statics[m_doorPosition.x][m_doorPosition.y]->setTexture(*Singleton<sf::Texture>::getInstance()->getResource("space"));
	m_statics[m_doorPosition.x][m_doorPosition.y] = move(std::make_shared<Space>(sf::Vector2f{ m_doorPosition.x*SIZE_SQUARE.first,m_doorPosition.y*SIZE_SQUARE.second }));
}
//=================draw===================================
void StageScreen::draw(sf::RenderWindow& window)const
{
	window.draw(m_backGround);
	drawBoard(window);
	m_score->display(window);
	m_time->display(window);
	if (m_explosion.first)
	{
		SingeltonSound::instance()->playExplosion();
		window.draw(m_explosion.second);
	}
	if (m_nemo->getIsDead())
	{
		sf::Sprite boomNemo(sf::Sprite(*Singleton<sf::Texture>::getInstance()->getResource("boomNemo")));
		boomNemo.setPosition({ m_nemo->getLocation().x-SIZE_SQUARE.first, m_nemo->getLocation().y - SIZE_SQUARE.second });
		window.draw(boomNemo);
	}
}
//=================checkCollition===================================
bool StageScreen::checkCollition(sf::RenderWindow& window)
{
	if (m_energizer->fullEnergy())
	{ 
		SingeltonSound::instance()->playOpenEnergizer();
		m_fullEnergy = true;
	}	
	passiveIterator iterator;
	bool b = true;
	for (iterator = m_passives.begin(); iterator != m_passives.end(); ++iterator)
	{
		(*iterator)->setLocation(sf::Vector2f{ (*iterator)->getLocation().x, (*iterator)->getLocation().y + SIZE_SQUARE.second });
		if (!(controlCollide(*iterator)))
			if (!m_explosion.first)
				(*iterator)->setLocation(sf::Vector2f{ (*iterator)->getLocation().x, (*iterator)->getLocation().y - SIZE_SQUARE.second });
			else
				break;
	}
	if (m_fullEnergy)
		if (m_energizer->pushNemo(*this))
		{
			m_nemo->setLocation(sf::Vector2f{ m_nemo->getLocation().x, m_nemo->getLocation().y + SIZE_SQUARE.second });
			SingeltonSound::instance()->playNemoEnergizer();
		}
	return b;
}
//=================getNemoPosition===================================
const sf::Vector2f & StageScreen::getNemoPosition() const
{
	return m_nemo->getLocation();
}
//=================drawToolBar===================================
void StageScreen::drawToolBar(sf::RenderWindow & window)const
{
	window.draw(m_backGroundToolbr);
	m_score->display(window);
	m_currLevel->display(window);
	m_time->display(window);
	m_energy->setInfo(std::string(std::to_string(m_energizer->getTotalBall() )+ "/" + std::to_string(m_energizer->getTotalBall())));
	m_energy->display(window);
	sf::Sprite lives(*Singleton<sf::Texture>::getInstance()->getResource("nemo"));
	lives.setScale(0.29f, 0.29f);
	unsigned gasp = 915;
	for (unsigned countLives = 1; countLives <= 3; countLives++, gasp += 22)
	{
		lives.setPosition(gasp, 35);
		if (countLives >m_nemo->getNUmLives())
			lives.setColor(sf::Color(180, 180, 180, 255));
		window.draw(lives);
	}
}
//=================positionOfTheNemo===================================
bool StageScreen::positionOfTheNemo(const sf::Vector2f& position) const
{
	return m_nemo->checkWithin(position);
}
//=================moveActive===================================
void StageScreen::moveActive()
{
	//std::for_each(m_activeObject.begin(), m_activeObject.end(), [(*this)](activeIterator iterator) {(*iterator)->movement(sf::Vector2f{ 520,550 }, (this)); })
	activeIterator iterator,copyIterator;
	for (iterator = m_activeObject.begin(); iterator != m_activeObject.end(); ++iterator)
	{
		(*iterator)->setOldPosition();
		(*iterator)->movement(*this);
		if (!controlCrash(*iterator))
			if (m_explosion.first)
				return;
			else
				(*iterator)->setLocation((*iterator)->getOldPosition());
	}
}
//=================explosion===================================
void StageScreen::explosion(const sf::Vector2f & position)
{
	m_explosion.first = true;
	if (inIntersectBomb(position, m_nemo))
	{
		m_nemo->isDead();
		if (m_nemo->getNUmLives() == 0)
			m_statusNemo = dead;
	}
	passiveIterator iterator;
	for (iterator = m_passives.begin(); iterator != m_passives.end(); ++iterator)
	{
		if (inIntersectBomb(position, *iterator))
		{
			m_passives.erase(iterator);
			break;
		}
	}
	m_activeObject.erase( std::remove_if(m_activeObject.begin(), m_activeObject.end(), [&](std::shared_ptr<ActiveObject> ptrActive) {return (inIntersectBomb(position, ptrActive)); }),m_activeObject.end());
	 std::cout << "size " << m_activeObject.size()<<"\n";
	int i = int((position.y) / SIZE_SQUARE.second);//Calculate the line which is a computer mouse
	int j = int((position.x) / SIZE_SQUARE.first);//Calculating column which is a computer mouse
	for (unsigned row = j - 1; row < j + 2; row++)
	{
		for (unsigned col = i-2; col < i+1; col++)
		{
			inIntersectBomb(position, m_statics[col][row]);
			m_statics[col][row] = move(std::make_shared<Space>(m_statics[col][row]->getLocation()));
		}
	}
	m_explosion.second.setPosition({ position.x - SIZE_SQUARE.first*2, position.y - SIZE_SQUARE.second*2 });
	
}
//=================inIntersectBomb===================================
bool StageScreen::inIntersectBomb(const sf::Vector2f& position, std::shared_ptr<Object> object)
{
	sf::Vector2f pos1{ position.x - SIZE_SQUARE.first, position.y - SIZE_SQUARE.second };
	sf::Vector2f pos2{ position.x, position.y - SIZE_SQUARE.second };
	sf::Vector2f pos3{ position.x + SIZE_SQUARE.first, position.y - SIZE_SQUARE.second };
	sf::Vector2f pos4{ position.x + SIZE_SQUARE.first, position.y };
	sf::Vector2f pos5{ position.x + SIZE_SQUARE.first, position.y + SIZE_SQUARE.second };
	sf::Vector2f pos6{ position.x, position.y + SIZE_SQUARE.second };
	sf::Vector2f pos7{ position.x - SIZE_SQUARE.first, position.y + SIZE_SQUARE.second };
	sf::Vector2f pos8{ position.x - SIZE_SQUARE.first, position.y };
	if (dynamic_cast<Exploding*>(object.get()) != nullptr)
	{
		if (object->checkWithin(pos1) || object->checkWithin(pos2) ||
			object->checkWithin(pos3) || object->checkWithin(pos4) ||
			object->checkWithin(pos5) || object->checkWithin(pos6) ||
			object->checkWithin(pos7) || object->checkWithin(pos8))
			return true;
	}
	else if (dynamic_cast<Moveable*>(object.get()))
	{
		if (object->checkWithin(pos1) || object->checkWithin(pos2) ||
			object->checkWithin(pos3) || object->checkWithin(pos4) ||
			object->checkWithin(pos5) || object->checkWithin(pos6) ||
			object->checkWithin(pos7) || object->checkWithin(pos8))
			//object->checkWithin(position))
		//setStaticSpace(position); return true;
			return true;
		if (object->checkWithin(position))
		{
			setStaticSpace(position); 
			return true;
		}
	}
	
	return false;
}
//=================controlCrash===================================
bool StageScreen::controlCrash(std::shared_ptr<Moveable> movable)
{
	pairIntersection st = getIntersectObj(movable);
	bool b = false;
	int count = 0;
	std::shared_ptr<Object>obj = nullptr;
	while (count < 4)
	{
		if (count == 0)
			obj = st.first.first;
		else if (count == 1)
			obj = st.first.second;
		else if (count == 2)
			obj = st.second.first;
		else if (count == 3)
			obj = st.second.second;
		//if (obj == nullptr)
		//return false;
		if (obj != nullptr)
		{
			std::weak_ptr<Object> weakActive = movable;
			b = processCollision(movable, obj, *this);
			if (!b)
			{
				if (weakActive.expired())
					movable->getSprite().setPosition(movable->getOldPosition());
				return b;
			}
		}
		count++;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return true;
}

//================controlCollide===================================
bool StageScreen::controlCollide(std::shared_ptr<Moveable>moveable)
{
	sf::Vector2f posActive = moveable->getLocation();
	activeIterator itActive = checkPositionActive(moveable);
	if (itActive != m_activeObject.end()&&(*itActive!=moveable))
		return processCollision(moveable, *itActive, *this);
	if (dynamic_cast<Nemo*>(moveable.get()) == nullptr&&
		m_nemo->checkWithin(moveable->getLocation()))
		return processCollision(moveable, m_nemo, *this);
	passiveIterator itPassive = checkPositionPassive(moveable);
	if (itPassive != m_passives.end()&&(*itPassive) != moveable)
	{
		if (dynamic_cast<Ball*>(moveable.get()) == nullptr&& dynamic_cast<Rock*>(moveable.get()) == nullptr
			&& dynamic_cast<Bomb*>(moveable.get()) == nullptr)
			return (processCollision(moveable, *itPassive, *this));
		std::shared_ptr<StaticObject>staticInThisPos = getStatic(posActive);
		return processCollision(moveable, staticInThisPos, *this);
	}
	std::shared_ptr<StaticObject>staticInThisPos = getStatic(posActive);
	return processCollision(moveable, staticInThisPos, *this);
}

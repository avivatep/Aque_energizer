#pragma once
#include <typeinfo>
#include <unordered_map>
#include "Exploding.h"
#include "NoExploding.h"
#include "Nemo.h"
#include "Crab.h"
#include "Ball.h"
#include "Rock.h"
#include "Bomb.h"
#include "Utilities.h"
#include "StageScreen.h"
#include "SingeltonSource.h"
#include "SingeltonSound.h"
#include "Energizer.h"
namespace {
	//nemo collide
	bool nemoBall(std::shared_ptr<Object> nemo, std::shared_ptr<Object> dirt, StageScreen&stage);
	bool nemoDirt(std::shared_ptr<Object> nemo, std::shared_ptr<Object> dirt,StageScreen&stage);
	bool nemoWall(std::shared_ptr<Object> nemo, std::shared_ptr<Object> wall, StageScreen&stage);
	bool nemoKey(std::shared_ptr<Object> nemo, std::shared_ptr<Object> key, StageScreen&stage);
	bool nemoSpace(std::shared_ptr<Object> nemo, std::shared_ptr<Object> space, StageScreen&stage);
	bool nemoGround(std::shared_ptr<Object> nemo, std::shared_ptr<Object> space, StageScreen&stage);
	bool nemoCrab(std::shared_ptr<Object>nemo, std::shared_ptr<Object> crab, StageScreen& stage);
	bool nemoEnergizer(std::shared_ptr<Object> nemo, std::shared_ptr<Object> energizer, StageScreen & stage);
	bool nemoRock(std::shared_ptr<Object> nemo, std::shared_ptr<Object> rock, StageScreen & stage);
	bool nemoBomb(std::shared_ptr<Object> nemo, std::shared_ptr<Object> bomb, StageScreen & stage);
	//ball collide
	bool ballNemo(std::shared_ptr<Object> ball, std::shared_ptr<Object> nemo, StageScreen&stage);
	bool ballCrab(std::shared_ptr<Object>ball, std::shared_ptr<Object> crab, StageScreen& stage);
	bool ballDirt(std::shared_ptr<Object> ball, std::shared_ptr<Object> dirt, StageScreen&stage);
	bool ballWall(std::shared_ptr<Object> ball, std::shared_ptr<Object> wall, StageScreen&stage);
	bool ballKey(std::shared_ptr<Object> ball, std::shared_ptr<Object> key, StageScreen&stage);
	bool ballSpace(std::shared_ptr<Object> ball, std::shared_ptr<Object> space, StageScreen&stage);
	bool ballGround(std::shared_ptr<Object> ball, std::shared_ptr<Object> ground, StageScreen&stage);
	bool ballEnergizer(std::shared_ptr<Object> ball, std::shared_ptr<Object> energizer, StageScreen & stage);
	bool ballRock(std::shared_ptr<Object> ball, std::shared_ptr<Object> rock, StageScreen & stage);
	bool ballBomb(std::shared_ptr<Object> ball, std::shared_ptr<Object> bomb, StageScreen & stage);
	//crab collide
	bool crabWall(std::shared_ptr<Object>crab, std::shared_ptr<Object> wall, StageScreen& stage);
	bool crabGround(std::shared_ptr<Object>crab, std::shared_ptr<Object> ground, StageScreen& stage);
	bool crabDirt(std::shared_ptr<Object>crab, std::shared_ptr<Object> dirt, StageScreen& stage);
	bool crabCrab(std::shared_ptr<Object>crab1, std::shared_ptr<Object> crab2, StageScreen& stage);
	bool crabSpace(std::shared_ptr<Object>crab, std::shared_ptr<Object> space, StageScreen& stage);
	bool crabNemo(std::shared_ptr<Object>crab, std::shared_ptr<Object> nemo, StageScreen& stage);
	bool crabBall(std::shared_ptr<Object>crab, std::shared_ptr<Object> ball, StageScreen& stage);
	bool crabRock(std::shared_ptr<Object> crab, std::shared_ptr<Object> rock, StageScreen & stage);
	bool crabBomb(std::shared_ptr<Object> crab, std::shared_ptr<Object> bomb, StageScreen & stage);
	//rock collide
	bool rockNemo(std::shared_ptr<Object> rock, std::shared_ptr<Object> nemo, StageScreen&stage);
	bool rockCrab(std::shared_ptr<Object>rock, std::shared_ptr<Object> crab, StageScreen& stage);
	bool rockDirt(std::shared_ptr<Object> rock, std::shared_ptr<Object> dirt, StageScreen&stage);
	bool rockWall(std::shared_ptr<Object> rock, std::shared_ptr<Object> wall, StageScreen&stage);
	bool rockKey(std::shared_ptr<Object> rock, std::shared_ptr<Object> key, StageScreen&stage);
	bool rockSpace(std::shared_ptr<Object> rock, std::shared_ptr<Object> space, StageScreen&stage);
	bool rockGround(std::shared_ptr<Object> rock, std::shared_ptr<Object> ground, StageScreen&stage);
	bool rockEnergizer(std::shared_ptr<Object> rock, std::shared_ptr<Object> energizer, StageScreen & stage);
	bool rockBall(std::shared_ptr<Object> rock, std::shared_ptr<Object> ball, StageScreen & stage);
	bool rockBomb(std::shared_ptr<Object> rock, std::shared_ptr<Object> bomb, StageScreen & stage);
	//bomb collide
	bool bombNemo(std::shared_ptr<Object> bomb, std::shared_ptr<Object> nemo, StageScreen&stage);
	bool bombCrab(std::shared_ptr<Object>bomb, std::shared_ptr<Object> crab, StageScreen& stage);
	bool bombDirt(std::shared_ptr<Object> bomb, std::shared_ptr<Object> dirt, StageScreen&stage);
	bool bombWall(std::shared_ptr<Object> bomb, std::shared_ptr<Object> wall, StageScreen&stage);
	bool bombKey(std::shared_ptr<Object> bomb, std::shared_ptr<Object> key, StageScreen&stage);
	bool bombSpace(std::shared_ptr<Object> bomb, std::shared_ptr<Object> space, StageScreen&stage);
	bool bombGround(std::shared_ptr<Object> bomb, std::shared_ptr<Object> ground, StageScreen&stage);
	bool bombEnergizer(std::shared_ptr<Object> bomb, std::shared_ptr<Object> energizer, StageScreen & stage);
	bool bombBall(std::shared_ptr<Object> bomb, std::shared_ptr<Object> ball, StageScreen & stage);
	bool bombRock(std::shared_ptr<Object> bomb, std::shared_ptr<Object> rock, StageScreen & stage);
	
	typedef bool(*HitFunctionPtr)(std::shared_ptr<Object>, std::shared_ptr<Object>,StageScreen&);
	typedef std::map<std::pair<std::string, std::string>, HitFunctionPtr>HitUnorderMap;
	HitUnorderMap initializeCollisionMap()
	{
		HitUnorderMap phm;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Dirt).name())] = &nemoDirt;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Wall).name())] = &nemoWall;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Key).name())] = &nemoKey;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Space).name())] = &nemoSpace;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Ground).name())] = &nemoGround;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Ball).name())] = &nemoBall;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Crab).name())] = &nemoCrab;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Rock).name())] = &nemoRock;
		phm[std::make_pair(typeid(Nemo).name(), typeid(Bomb).name())] = &nemoBomb;

		phm[std::make_pair(typeid(Ball).name(), typeid(Dirt).name())] = &ballDirt;
		phm[std::make_pair(typeid(Ball).name(), typeid(Wall).name())] = &ballWall;
		phm[std::make_pair(typeid(Ball).name(), typeid(Key).name())] = &ballKey;
		phm[std::make_pair(typeid(Ball).name(), typeid(Space).name())] = &ballSpace;
		phm[std::make_pair(typeid(Ball).name(), typeid(Ground).name())] = &ballGround;
		phm[std::make_pair(typeid(Ball).name(), typeid(Nemo).name())] = &ballNemo;
		phm[std::make_pair(typeid(Ball).name(), typeid(Energizer).name())] = &ballEnergizer;
		phm[std::make_pair(typeid(Ball).name(), typeid(Crab).name())] = &ballCrab;
		phm[std::make_pair(typeid(Ball).name(), typeid(Rock).name())] = &ballRock;
		phm[std::make_pair(typeid(Ball).name(), typeid(Bomb).name())] = &ballBomb;

		phm[std::make_pair(typeid(Crab).name(), typeid(Wall).name())] = &crabWall;
		phm[std::make_pair(typeid(Crab).name(), typeid(Ground).name())] =&crabGround;
		phm[std::make_pair(typeid(Crab).name(), typeid(Dirt).name())] = &crabDirt;
		phm[std::make_pair(typeid(Crab).name(), typeid(Crab).name())] = &crabCrab;
		phm[std::make_pair(typeid(Crab).name(), typeid(Space).name())] = &crabSpace;
		phm[std::make_pair(typeid(Crab).name(), typeid(Nemo).name())] = &crabNemo;
		phm[std::make_pair(typeid(Crab).name(), typeid(Ball).name())] = &crabBall;
		phm[std::make_pair(typeid(Crab).name(), typeid(Rock).name())] = &crabRock;
		phm[std::make_pair(typeid(Crab).name(), typeid(Bomb).name())] = &crabBomb;
	
		phm[std::make_pair(typeid(Rock).name(), typeid(Dirt).name())] = &rockDirt;
		phm[std::make_pair(typeid(Rock).name(), typeid(Wall).name())] = &rockWall;
		phm[std::make_pair(typeid(Rock).name(), typeid(Key).name())] = &rockKey;
		phm[std::make_pair(typeid(Rock).name(), typeid(Space).name())] = &rockSpace;
		phm[std::make_pair(typeid(Rock).name(), typeid(Ground).name())] = &rockGround;
		phm[std::make_pair(typeid(Rock).name(), typeid(Nemo).name())] = &rockNemo;
		phm[std::make_pair(typeid(Rock).name(), typeid(Energizer).name())] = &rockEnergizer;
		phm[std::make_pair(typeid(Rock).name(), typeid(Crab).name())] = &rockCrab;
		phm[std::make_pair(typeid(Rock).name(), typeid(Ball).name())] = &rockBall;
		phm[std::make_pair(typeid(Rock).name(), typeid(Bomb).name())] = &rockBomb;

		phm[std::make_pair(typeid(Bomb).name(), typeid(Dirt).name())] = &bombDirt;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Wall).name())] = &bombWall;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Key).name())] = &bombKey;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Space).name())] = &bombSpace;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Ground).name())] = &bombGround;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Nemo).name())] = &bombNemo;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Energizer).name())] = &bombEnergizer;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Crab).name())] = &bombCrab;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Ball).name())] = &bombBall;
		phm[std::make_pair(typeid(Bomb).name(), typeid(Rock).name())] = &bombRock;
		return phm;
	}
	bool nemoGround(std::shared_ptr<Object> nemo, std::shared_ptr<Object> space, StageScreen&stage)
	{
		return false;
	}
	bool nemoCrab(std::shared_ptr<Object> nemo, std::shared_ptr<Object> crab, StageScreen & stage)
	{
		stage.explosion(crab->getLocation());
		return false;
	}
	bool nemoSpace(std::shared_ptr<Object>nemo, std::shared_ptr<Object> space, StageScreen&stage)
	{
		return true;
	}
	bool nemoWall(std::shared_ptr<Object> nemo, std::shared_ptr<Object> wall, StageScreen&stage)
	{
		return false;
	}
	bool nemoKey(std::shared_ptr<Object> nemo, std::shared_ptr<Object> key, StageScreen & stage)
	{
		key->setTexture(*Singleton<sf::Texture>::getInstance()->getResource("space"));
		SingeltonSound::instance()->playOpenGate();
		stage.deleteDoor();
		
		return true;
	}
	bool nemoEnergizer(std::shared_ptr<Object> nemo, std::shared_ptr<Object> energizer, StageScreen & stage)
	{
		nemo->setLocation(sf::Vector2f{ nemo->getLocation().x, nemo->getLocation().y + SIZE_SQUARE.second / 2 });
		//stage.deleteDoor();

		return true;
	}
	bool nemoBomb(std::shared_ptr<Object> nemo, std::shared_ptr<Object> bomb, StageScreen & stage)
	{
		Bomb* bombConvert = static_cast<Bomb*>(bomb.get());
		Nemo* nemoConvert = static_cast<Nemo*>(nemo.get());
		bombConvert->setDirection(nemoConvert->getDirection());
		return bombConvert->movement(stage);
	}
	bool crabRock(std::shared_ptr<Object> ball, std::shared_ptr<Object> rock, StageScreen & stage)
	{
		return false;
	}
	bool crabWall(std::shared_ptr<Object> crab, std::shared_ptr<Object> wall, StageScreen&stage)
	{
		return false;
	}
	bool crabGround(std::shared_ptr<Object>crab, std::shared_ptr<Object> ground, StageScreen& stage)
	{
		return false;
	}
	bool crabCrab(std::shared_ptr<Object>crab1, std::shared_ptr<Object> crab2, StageScreen& stage)
	{
		return false;
	}
	bool crabDirt(std::shared_ptr<Object>crab, std::shared_ptr<Object> dirt, StageScreen& stage)
	{
		return false;
	}
	bool crabSpace(std::shared_ptr<Object>crab, std::shared_ptr<Object> space, StageScreen& stage)
	{
		return true;
	}
	bool crabNemo(std::shared_ptr<Object> crab, std::shared_ptr<Object> nemo, StageScreen & stage)
	{
		stage.explosion(crab->getLocation());
		return false;
	}
	bool crabBall(std::shared_ptr<Object> crab, std::shared_ptr<Object> ball, StageScreen & stage)
	{
		return false;
	}
	bool crabBomb(std::shared_ptr<Object> crab, std::shared_ptr<Object> bomb, StageScreen & stage)
	{
		return false;
	}
	bool nemoBall(std::shared_ptr<Object> nemo, std::shared_ptr<Object> ball, StageScreen & stage)
	{
		Ball* ballConvert = static_cast<Ball*>(ball.get());
		Nemo* nemoConvert = static_cast<Nemo*>(nemo.get());
		ballConvert->setDirection(nemoConvert->getDirection());
		return ballConvert->movement(stage);
	}
	bool nemoRock(std::shared_ptr<Object> nemo, std::shared_ptr<Object> rock, StageScreen & stage)
	{
		Rock* rockConvert = static_cast<Rock*>(rock.get());
		Nemo* nemoConvert = static_cast<Nemo*>(nemo.get());
		rockConvert->setDirection(nemoConvert->getDirection());
		return rockConvert->movement(stage);
	}
	bool ballNemo(std::shared_ptr<Object> ball, std::shared_ptr<Object> nemo, StageScreen & stage)
	{
		//stage.explosion(ball->getLocation());
		return false;
	}
	bool ballCrab(std::shared_ptr<Object> ball, std::shared_ptr<Object> crab, StageScreen & stage)
	{
		return false;
	}
	bool ballDirt(std::shared_ptr<Object> ball, std::shared_ptr<Object> dirt, StageScreen & stage)
	{
		return false;
	}
	bool ballRock(std::shared_ptr<Object> ball, std::shared_ptr<Object> rock, StageScreen & stage)
	{
		return false;
	}
	bool ballWall(std::shared_ptr<Object> ball, std::shared_ptr<Object> wall, StageScreen & stage)
	{
		return false;
	}
	bool ballKey(std::shared_ptr<Object> ball, std::shared_ptr<Object> key, StageScreen & stage)
	{
		return false;
	}
	bool ballSpace(std::shared_ptr<Object> ball, std::shared_ptr<Object> space, StageScreen & stage)
	{
		ball->setLocation(space->getLocation());
		std::this_thread::sleep_for(std::chrono::milliseconds(20));	// sleep for to see the ball 
		return true;
	}
	bool ballGround(std::shared_ptr<Object> ball, std::shared_ptr<Object> ground, StageScreen & stage)
	{
		return false;
	}
	bool ballEnergizer(std::shared_ptr<Object> ball, std::shared_ptr<Object> energizer, StageScreen & stage)
	{
		Energizer* ener = static_cast<Energizer*>(energizer.get());
		ener->subBall();
		stage.setScore(10);
		stage.setStaticSpace(ball->getLocation());
		return false;
	}
	bool ballBomb(std::shared_ptr<Object> ball, std::shared_ptr<Object> bomb, StageScreen & stage)
	{
		return false;
	}
	bool nemoDirt(std::shared_ptr<Object> nemo, std::shared_ptr<Object> dirt,StageScreen& stage)
	{
		stage.setStaticSpace(dirt->getLocation());
		return true;
	}
	bool rockNemo(std::shared_ptr<Object> rock, std::shared_ptr<Object> nemo, StageScreen&stage)
	{
		return false;
	}
	bool rockCrab(std::shared_ptr<Object>rock, std::shared_ptr<Object> crab, StageScreen& stage)
	{
		stage.explosion(rock->getLocation());
		return false;
	}
	bool rockDirt(std::shared_ptr<Object> rock, std::shared_ptr<Object> dirt, StageScreen&stage)
	{
		return false;
	}
	bool rockWall(std::shared_ptr<Object> rock, std::shared_ptr<Object> wall, StageScreen&stage)
	{
		return false;
	}
	bool rockKey(std::shared_ptr<Object> rock, std::shared_ptr<Object> key, StageScreen&stage)
	{
		return false;
	}
	bool rockSpace(std::shared_ptr<Object> rock, std::shared_ptr<Object> space, StageScreen&stage)
	{
		return true;
	}
	bool rockGround(std::shared_ptr<Object> rock, std::shared_ptr<Object> ground, StageScreen&stage)
	{
		return false;
	}
	bool rockEnergizer(std::shared_ptr<Object> rock, std::shared_ptr<Object> energizer, StageScreen & stage)
	{
		return false;
	}
	bool rockBall(std::shared_ptr<Object> rock, std::shared_ptr<Object> ball, StageScreen & stage)
	{
		return false;
	}
	bool rockBomb(std::shared_ptr<Object> rock, std::shared_ptr<Object> bomb, StageScreen & stage)
	{
		return false;
	}
	bool bombNemo(std::shared_ptr<Object> bomb, std::shared_ptr<Object> nemo, StageScreen&stage)
	{
		stage.explosion(bomb->getLocation());
		return false;
	}
	bool bombCrab(std::shared_ptr<Object>bomb, std::shared_ptr<Object> crab, StageScreen& stage)
	{
		stage.explosion(bomb->getLocation());
		return false;
	}
	bool bombDirt(std::shared_ptr<Object> bomb, std::shared_ptr<Object> dirt, StageScreen&stage)
	{
		stage.explosion(bomb->getLocation());
		return false;
	}
	bool bombWall(std::shared_ptr<Object> bomb, std::shared_ptr<Object> wall, StageScreen&stage)
	{
		return false;
	}
	bool bombKey(std::shared_ptr<Object> bomb, std::shared_ptr<Object> key, StageScreen&stage)
	{
		stage.explosion(bomb->getLocation());
		return false;
	}
	bool bombSpace(std::shared_ptr<Object> bomb, std::shared_ptr<Object> space, StageScreen&stage)
	{
		return true;
	}
	bool bombGround(std::shared_ptr<Object> bomb, std::shared_ptr<Object> ground, StageScreen&stage)
	{
		stage.explosion(bomb->getLocation());
		return false;
	}
	bool bombEnergizer(std::shared_ptr<Object> bomb, std::shared_ptr<Object> energizer, StageScreen & stage)
	{
		return false;
	}
	bool bombBall(std::shared_ptr<Object> bomb, std::shared_ptr<Object> ball, StageScreen & stage)
	{
		stage.explosion(bomb->getLocation());
		return false;
	}
	bool bombRock(std::shared_ptr<Object> bomb, std::shared_ptr<Object> rock, StageScreen & stage)
	{
		stage.explosion(bomb->getLocation());
		return false;
	}
	HitFunctionPtr lookup(const std::string& class1,const std::string& class2)
	{
		static HitUnorderMap collisionMap(initializeCollisionMap());
		HitUnorderMap::const_iterator mapEntry = collisionMap.find(make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
			return 0;
		return (*mapEntry).second;
	}

} // end namespace

	


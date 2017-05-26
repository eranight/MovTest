#include "Engine.h"
#include "Sector.h"

USING_NS_CC;

using namespace AstralGame;

const std::string Engine::NAME = "engine";

Engine::Engine(Sector * sector, cocos2d::Node * user, cocos2d::ParticleSystem * view /*= nullptr*/) :
sector(sector), user(user), view(view), edgeSectorCollisionReaction(nullptr)
{
	angle = rotDirection = rotVelocity = 0.0f;
	movDirection = Vec2::ZERO;
	maxMovVelocity = currMovVelocity = 0.0f;

	//it is important, cause in all methods use sector and user without verification
	CCASSERT(sector != nullptr, "Sector shouldn't be null!");
	CCASSERT(user != nullptr, "User shouldn't be null!");
}

Engine * Engine::create(Sector * sector, cocos2d::Node * user, cocos2d::ParticleSystem * view/* = nullptr*/)
{
	Engine * ret = new (std::nothrow) Engine(sector, user, view);
	if (ret != nullptr && ret->init())
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

//common interface

bool Engine::init()
{
	if (!Component::init())
		return false;
	setName(NAME);
	return true;
}

void Engine::update(float dt)
{
	if (rotDirection != 0.0f)
		turnToAngle(angle + rotVelocity * dt * rotDirection);

	if (currMovVelocity != 0.0f)
	{
		auto nextPos = user->getPosition() + movDirection * currMovVelocity * dt;

		//if next pos is in sector we change user's position
		if (sector->checkValidPosition(nextPos))
			user->setPosition(nextPos);
		//if next pos is out of sector we call collision reaction lambda if it exist
		else if (edgeSectorCollisionReaction != nullptr)
			edgeSectorCollisionReaction(nextPos);
		//else we just stop movement
		else
			currMovVelocity = 0.0f;
	}

	//work with view
	if (view != nullptr)
	{
		if (view->isPaused())
		{
			if (currMovVelocity != 0.0f)
				view->resumeEmissions();
		}
		else
		{
			if (currMovVelocity == 0.0f)
				view->pauseEmissions();
		}
	}
}

//rotation interface

void Engine::turnToAngle(float angle)
{
	this->angle = angle;

	//in radian positiv angle - ccw, negative - cw
	//in dergees positiv angle - cw, negative - ccw
	//that is why it need minus!
	movDirection = Vec2::forAngle(-CC_DEGREES_TO_RADIANS(angle));
	user->setRotation(angle);
}

//movement interface

void Engine::setMaxMovVelocity(float maxMovVelocity)
{
	CCASSERT(maxMovVelocity >= 0.0f, "maxMovVelocity shouldn't be nagative");
	
	//if current velocity equals max velocity but no equal zero, we need to reduce it
	if (this->maxMovVelocity < maxMovVelocity && currMovVelocity != 0.0f && currMovVelocity == this->maxMovVelocity)
	{
		currMovVelocity = maxMovVelocity;
	}
	this->maxMovVelocity = maxMovVelocity;
}

void Engine::setCurrMovVelocity(float currMovVelocity)
{
	CCASSERT(currMovVelocity >= 0.0f, "currMovVelocity shouldn't be nagative");

	//current velocity can't be greater max velocity
	if (currMovVelocity > maxMovVelocity)
		currMovVelocity = maxMovVelocity;
	this->currMovVelocity = currMovVelocity;
}

void Engine::setMovDirection(const Vec2 & movDirection)
{
	this->movDirection = movDirection.getNormalized();
}
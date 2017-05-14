#include "AgressiveBehavior.h"
#include "Ship.h"
#include "Engine.h"
#include "Canon.h"
#include "BrickClasses\Parameters.h"
#include "Properties\Hittable.h"

USING_NS_CC;

using namespace AstralGame;

AgressiveBehavior::AgressiveBehavior(Engine * engine, Canon * canon, float maxFireDistance, float minFireDistance, float velocity) :
engine(engine), canon(canon), target(nullptr), maxFireDistance(maxFireDistance), minFireDistance(minFireDistance), velocity(velocity)
{
	CCASSERT(engine != nullptr, "Engine shouldn't be null!");
	CCASSERT(canon != nullptr, "Canon shouldn't be null!");
	CCASSERT(maxFireDistance >= minFireDistance, "masFireDistance should be greater or equal minFireDistance!");
	/*engine->edgeSectorCollisionReaction = [this](const Vec2 & nextPos)
	{

	};*/
}

void AgressiveBehavior::start(Node * target)
{
	this->target = target;
	engine->setCurrMovVelocity(velocity);
	mode = 1;

	hittable = dynamic_cast<Parameters *>(target->getUserObject())->getProperty<Hittable *>(PROPS_TYPE::hittable);
}

void AgressiveBehavior::stop()
{
	target = nullptr;
}

void AgressiveBehavior::update(float dt)
{
	CCASSERT(target != nullptr, "Target shouldn't be null!");

	if (hittable->isDead())
	{
		targetIsDeadReaction();
		return;
	}

	const Vec2 & ownpos = engine->getUser()->getPosition();
	const Vec2 & shppos = target->getPosition();
	float faceangle = -CC_RADIANS_TO_DEGREES((shppos - ownpos).getAngle());

	switch (mode)
	{
	case 1:
		if (ownpos.distance(shppos) > minFireDistance)
		{
			engine->turnToAngle(faceangle);
			if (engine->getCurrMovVelocity() == 0.0f)
			{
				engine->setCurrMovVelocity(velocity);
			}
		}
		else
		{
			engine->setCurrMovVelocity(0.0f);
			mode = 2;
		}
		break;
	case 2:
		if (ownpos.distance(shppos) > maxFireDistance)
		{
			mode = 1;
		}
		else
		{
			engine->turnToAngle(faceangle);
			if (canon->isReady())
			{
				canon->shot(target);
			}
		}
		break;
	}
}

void AgressiveBehavior::setMinFireDistance(float minFireDistance)
{
	//we need to recalculate movement


	this->minFireDistance = minFireDistance;
}

void AgressiveBehavior::setMaxFireDistance(float maxFireDistance)
{
	//we need to recalculate movement


	this->maxFireDistance = maxFireDistance;
}

void AgressiveBehavior::setVelocity(float velocity)
{
	//we need to recalculate velocity


	this->velocity = velocity;
}
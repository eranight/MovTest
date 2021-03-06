#include "Monster.h"
#include "Ship.h"
#include "Components\TrackingTarget.h"
#include "Properties\Observer.hpp"

USING_NS_CC;

using namespace AstralGame;

Monster * Monster::create(Sector * sector, float trackingDistance)
{
	Monster * ret = new (std::nothrow) Monster();
	if (ret != nullptr && ret->init(sector, trackingDistance))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

Monster::Monster() :
body(nullptr), engine(nullptr), canon(false), calmBehavior(nullptr), agressiveBehavior(nullptr), target(nullptr)
{
}

Monster::~Monster()
{
	if (canon != nullptr)
		CC_SAFE_DELETE(canon);
	if (calmBehavior != nullptr)
		CC_SAFE_DELETE(calmBehavior);
	if (agressiveBehavior != nullptr)
		CC_SAFE_DELETE(agressiveBehavior);
}

bool Monster::init(Sector * sector, float trackingDistance)
{
	if (!Node::init())
		return false;

	body = Sprite::create("monster.png");
	if (body == nullptr)
	{
		CCLOG("Failed create body");
		return false;
	}

	parameters = Parameters::create();
	if (parameters == nullptr)
	{
		CCLOG("Failed create parameters!");
		return false;
	}
	this->setUserObject(parameters);

	engine = Engine::create(sector, this);
	if (engine == nullptr)
	{
		CCLOG("Failed create engine");
		return false;
	}
	this->addComponent(engine);
	engine->setMaxMovVelocity(140.0f);

	auto parameters = Parameters::create();
	if (parameters == nullptr)
	{
		CCLOG("Failed create Parameters");
		return false;
	}
	this->setUserObject(parameters);

	auto observer = Observer::create();
	if (observer == nullptr)
	{
		CCLOG("Failed create observer");
		return false;
	}
	observer->loseTargetReaction = [this]()
	{
		this->behaviorMode = 1;
		this->calmBehavior->start();
		this->agressiveBehavior->stop();
	};
	parameters->addPropertry(observer);

	auto trackingTarget = TrackingTarget::create(trackingDistance);
	if (trackingTarget == nullptr)
	{
		CCLOG("Failed create trackingTarget");
		return false;
	}
	this->addComponent(trackingTarget);
	trackingTarget->targetIsInTrakcingZoneReaction = [this, trackingTarget, observer](Node * target)
	{
		this->behaviorMode = 2;
		this->calmBehavior->stop();
		this->agressiveBehavior->start(target);
		trackingTarget->setEnabled(false);
		observer->captureTarget(target);
	};

	canon = new (std::nothrow) Canon(sector, this, Vec2(18.5f, 0.0f), 1.5f);
	if (canon == nullptr)
	{
		CCLOG("Failed create canon");
		return false;
	}

	calmBehavior = new (std::nothrow) CalmBehavior(engine, 2.0f, 2.0f, 70.0f);
	if (calmBehavior == nullptr)
	{
		CCLOG("Failed create calmBehavior");
		CC_SAFE_DELETE(canon);
		return false;
	}

	agressiveBehavior = new (std::nothrow) AgressiveBehavior(engine, canon, 300.0f, 250.0f, 140.0f);
	if (agressiveBehavior == nullptr)
	{
		CCLOG("Failed create agressiveBehavior");
		CC_SAFE_DELETE(canon);
		CC_SAFE_DELETE(calmBehavior);
		return false;
	}

	this->addChild(body, 1);
	behaviorMode = 1;
	calmBehavior->start();
	engine->turnToAngle(-90.0f);

	scheduleUpdate();

	return true;
}

void Monster::update(float dt)
{
	Node::update(dt);
	canon->update(dt);

	if (behaviorMode == 1)
	{
		calmBehavior->update(dt);
	}
	else
	{
		agressiveBehavior->update(dt);
	}
}
#include "Portal.h"
#include "BrickClasses\Engine.h"
#include "Sector.h"

USING_NS_CC;
using namespace AstralGame;

bool Portal::init(const Vec2 & positonForTarget)
{
	if (!Node::init())
		return false;

	view = Sprite::create("spiral.png");
	if (view == nullptr)
	{
		CCLOG("Failed create View");
		return false;
	}
	view->setPosition(Vec2::ZERO);
	view->setColor(Color3B::MAGENTA);
	view->runAction(RepeatForever::create(RotateBy::create(10.0f, 360.0f)));

	this->addChild(view);
	this->positionForTarget = positonForTarget;

	this->target = nullptr;

	scheduleUpdate();

	return true;
}

void Portal::update(float dt)
{
	Node::update(dt);

	if (target != nullptr)
	{
		if (this->getPosition().distance(target->getPosition()) < 48.0f)
		{
			teleportationIn(target);
		}
	}
}

void Portal::teleportationIn(Node * target)
{
	dynamic_cast<Sector *>(this->getParent())->setNodeUnobtainable(target);
}

void Portal::teleportationOut(Node * target)
{
	target->setPosition(convertToWorldSpace(positionForTarget));
	float angle = -CC_RADIANS_TO_DEGREES((target->getPosition() - getPosition()).getAngle());
	Engine * engine = dynamic_cast<Engine *>(target->getComponent(Engine::NAME));
	engine->setCurrMovVelocity(0.0f);
	engine->turnToAngle(angle);
	dynamic_cast<Sector *>(this->getParent())->setNodeObtainable(target);
}

InnerPortal * InnerPortal::create(const Vec2 & positionForTarget)
{
	auto ret = new (std::nothrow) InnerPortal();
	if (ret != nullptr && ret->init(positionForTarget))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

bool InnerPortal::init(const Vec2 & positionForTarget)
{
	if (!Portal::init(positionForTarget))
		return false;

	exitPortal = nullptr;
}

void InnerPortal::teleportationIn(Node * target)
{
	Portal::teleportationIn(target);
	
	CCASSERT(exitPortal != nullptr, "ExitPortal shouldn't be null!");
	exitPortal->teleportationOut(target);
}
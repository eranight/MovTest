#include "Portal.h"
#include "BrickClasses\Engine.h"
#include "Sector.h"

USING_NS_CC;
using namespace AstralGame;

Portal * Portal::create(Vec2 positonForTarget)
{
	auto ret = new (std::nothrow) Portal();
	if (ret != nullptr && ret->init(positonForTarget))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

bool Portal::init(Vec2 positonForTarget)
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
	this->positonForTarget = positonForTarget;

	this->exitPortal = nullptr;
	this->target = nullptr;

	scheduleUpdate();

	return true;
}

void Portal::update(float dt)
{
	Node::update(dt);

	if (target != nullptr && exitPortal != nullptr)
	{
		if (this->getPosition().distance(target->getPosition()) < 48.0f)
		{
			dynamic_cast<Sector *>(this->getParent())->setNodeUnobtainable(target);
			exitPortal->movingTarget(target);
		}
	}
}

void Portal::movingTarget(Node * target)
{
	target->setPosition(convertToWorldSpace(positonForTarget));
	float angle = -CC_RADIANS_TO_DEGREES((target->getPosition() - getPosition()).getAngle());
	Engine * engine = dynamic_cast<Engine *>(target->getComponent(Engine::NAME));
	engine->setCurrMovVelocity(0.0f);
	engine->turnToAngle(angle);
	dynamic_cast<Sector *>(this->getParent())->setNodeObtainable(target);
}
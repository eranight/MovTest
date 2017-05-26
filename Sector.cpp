#include "Sector.h"
#include "Monster.h"
#include "ObjectsFactory.h"
#include "ComponentsFactory.h"
#include "Components\TrackingTarget.h"
#include "Portal.h"
#include "BrickClasses\Parameters.h"
#include "Properties\Observed.hpp"
#include "Properties\Observer.hpp"

USING_NS_CC;

using namespace AstralGame;

Sector::~Sector()
{
	if (_objFactory != nullptr)
		_objFactory->release();
	if (_comFactory != nullptr)
		_comFactory->release();
}

Scene* Sector::createScene()
{
	auto scene = Scene::create();

	auto layer = Sector::create();

	scene->addChild(layer);

	return scene;
}

bool Sector::init()
{
	if (!Layer::init())
		return false;

	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	eventListenerKeyboard = EventListenerKeyboard::create();

	if (!createFactories())
		return false;

	if (!createPortals())
		return false;

	if (!createMontster())
		return false;

	auto circleBoard = DrawNode::create();
	circleBoard->drawCircle(_origin + _visibleSize * 0.5f, _visibleSize.height * 0.5f, 0.0f, 36, false, Color4F::RED);

	this->addChild(circleBoard, 0);

	
	_eventDispatcher->addEventListenerWithFixedPriority(eventListenerKeyboard, 30);

	scheduleUpdate();

	setNodeObtainable(ship);

	return true;
}

bool Sector::createPortals()
{
	Portal * p1 = InnerPortal::create("portal2", Vec2(0.0f, -64.0f));
	p1->setPosition(_origin + Size(_visibleSize.width * 0.5f, _visibleSize.height - 48.0f));
	this->addChild(p1, 0, "portal1");

	if (!createShip())
		return false;
	p1->teleportationOut(ship);

	Portal * p2 = InnerPortal::create("portal1", Vec2(0.0f, 64.0f));
	p2->setPosition(_origin + Size(_visibleSize.width * 0.5f, 48.0f));
	this->addChild(p2, 0, "portal2");

	p1->setTarget(ship);
	p2->setTarget(ship);

	return true;
}

bool Sector::createFactories()
{
	_objFactory = ObjectsFactory::create();
	if (_objFactory == nullptr)
	{
		CCLOG("Failed create ObjectsFactory!");
		return false;
	}
	_objFactory->retain();

	_comFactory = ComponentsFactory::create();
	if (_comFactory == nullptr)
	{
		CCLOG("Failed create ComponentsFactory!");
		return false;
	}
	_comFactory->retain();
	
	return true;
}


bool Sector::createShip()
{
	ship = AstralGame::Ship::create(this);
	CCASSERT(ship != nullptr, "Ship is null!");
	ship->setPosition(_origin + _visibleSize * 0.5f);
	this->addChild(ship, 1, "ship");

	auto engine = ship->getEngine();

	eventListenerKeyboard->onKeyPressed = [engine, this](EventKeyboard::KeyCode keyCode, Event * event)
	{

		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (engine->getRotDirection() == 0.0f) engine->setLeftRotDirection();
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (engine->getRotDirection() == 0.0f) engine->setRightRotDirection();
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			engine->setCurrMovVelocity(70.0f);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			engine->setCurrMovVelocity(0.0f);
			break;
		case EventKeyboard::KeyCode::KEY_0:
			engine->turnToAngle(engine->getRotAngle() + 90.0f);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
		{
												  this->setNodeUnobtainable(this->getChildByName("ship"));
		}
			break;
		case EventKeyboard::KeyCode::KEY_D:
			dynamic_cast<Ship *>(this->getChildByName("ship"))->setDead();
			break;
		default:
			break;
		}

	};

	eventListenerKeyboard->onKeyReleased = [engine](EventKeyboard::KeyCode keyCode, Event * event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (engine->getRotDirection() == -1.0f) engine->resetRotDirection();
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (engine->getRotDirection() == 1.0f) engine->resetRotDirection();
			break;
		}
	};

	return true;
}

bool Sector::createMontster()
{
	auto monster = Monster::create(this, 400.0f);
	CCASSERT(monster != nullptr, "Monster is null!");
	monster->setPosition(_origin + _visibleSize * 0.25f);
	this->addChild(monster, 1, "monster");

	monster = Monster::create(this, 400.0f);
	CCASSERT(monster != nullptr, "Monster is null!");
	monster->setPosition(_origin + _visibleSize * 0.75f);
	this->addChild(monster, 1, "monster");

	auto target = ship;
	this->enumerateChildren("//monster",
		[&target](cocos2d::Node * monster)
		{
			dynamic_cast<TrackingTarget *>(monster->getComponent(TrackingTarget::NAME))->setTarget(target);
			return false;
		}
	);

	return true;
}

void Sector::update(float dt)
{
	Layer::update(dt);

}

bool Sector::checkValidPosition(const Vec2 & pos)
{
	return (_origin + _visibleSize * 0.5f).distance(pos) < _visibleSize.height * 0.5f;
}

void Sector::setNodeUnobtainable(Node * node, bool resetBullets/* = true*/)
{
	auto children = this->getChildren();
	for (auto & child : children)
	{
		auto component = child->getComponent(TrackingTarget::NAME);
		if (component != nullptr)
		{
			auto trackingTarget = dynamic_cast<TrackingTarget *>(component);
			if (trackingTarget->getTarget() == node)
				trackingTarget->setEnabled(false);

		}
	}
	PARAMS(node)->getProperty<Observed *>(PROPS_TYPE::observed)->resetObserver();
}

void Sector::setNodeObtainable(Node * node)
{
	if (node == ship)
		this->enumerateChildren("//monster",
			[&node](cocos2d::Node * monster)
			{
				dynamic_cast<TrackingTarget *>(monster->getComponent(TrackingTarget::NAME))->setEnabled(true);
				return false;
			}
		);
}

void Sector::setNodeDead(Node * node)
{
	if (node == ship)
	{
		this->enumerateChildren("//monster",
		[&node](cocos2d::Node * monster)
		{
			dynamic_cast<TrackingTarget *>(monster->getComponent(TrackingTarget::NAME))->setTarget(nullptr);
			return false;
		}
		);
		PARAMS(node)->getProperty<Observed *>(PROPS_TYPE::observed)->resetObserver();
	}
}
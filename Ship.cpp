#include "Ship.h"
#include "Components\AttackingBullets.h"
#include "Properties\Hittable.h"
#include "BrickClasses\Parameters.h"
#include "Sector.h"

USING_NS_CC;

using namespace AstralGame;

Ship::Ship() : hall(nullptr), engine(nullptr) {}


Ship * Ship::create(Sector * sector)
{
	Ship * ret = new (std::nothrow) Ship();
	if (ret != nullptr && ret->init(sector))
	{
		ret->autorelease();
	}
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

bool Ship::init(Sector * sector)
{
	if (!Node::init())
		return false;

	hall = Sprite::create("ship_5.png");

	if (hall == nullptr)
	{
		CCLOG("Failed create hall");
		return false;
	}

	auto ps = ParticleMeteor::create();
	if (ps == nullptr)
	{
		CCLOG("Failed create ps");
		return false;
	}
	ps->setStartSize(15.0f);
	ps->setEndSize(1.0f);
	ps->setPosition(Vec2(-hall->getContentSize().height * 0.5f, 0.0f));
	ps->setLife(0.4f);
	ps->setTotalParticles(200);
	ps->setEmitterMode(ParticleSystem::Mode::RADIUS);

	engine = Engine::create(sector, this, ps);
	if (engine == nullptr)
	{
		CCLOG("Failed create engine");
		//we do not need to delete body, cause it is autorelease!
		return false;
	}
	this->addComponent(engine);
	engine->setMaxMovVelocity(140.0f);
	engine->setRotVelocity(70.0f);

	this->addChild(hall, 1);
	this->addChild(ps, 0);
	engine->turnToAngle(-90.0f);

	auto attackingBullets = AttackingBullets::create(20.0f);
	if (attackingBullets == nullptr)
	{
		CCLOG("Failed create component AttackingBullets");
		return false;
	}
	attackingBullets->setName(AttackingBullets::NAME);
	this->addComponent(attackingBullets);

	auto parameters = Parameters::create();
	if (parameters == nullptr)
	{
		CCLOG("Failed create Parameters");
		return false;
	}
	this->setUserObject(parameters);

	auto hittable = Hittable::create(1200);
	if (hittable == nullptr)
	{
		CCLOG("Failed create property Hittable");
		return false;
	}
	hittable->deadevent = [sector, this]()
	{
		sector->setNodeUnobtainable(this);
	};
	if (!parameters->addPropertry(hittable))
	{
		CCLOG("Failed add property Hittable");
	}

	scheduleUpdate();

	return true;
}

void Ship::update(float dt)
{
	Node::update(dt);
}

void Ship::setDead()
{
	auto hittable = dynamic_cast<Parameters *>(_userObject)->getProperty<Hittable *>(PROPS_TYPE::hittable);
	hittable->impactDamage(1000);
}
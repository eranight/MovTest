#include "Bullet.h"
#include "Sector.h"
#include "BrickClasses\Engine.h"
#include "Components\AttackingBullets.h"

USING_NS_CC;

using namespace AstralGame;

Bullet::Bullet() : engine(nullptr), attackingBulletsComponent(nullptr), targetPosition(Vec2::ZERO), view(nullptr), velocity(0.0f), damageDistance(0.0f), dead(false)
{
}

Bullet * Bullet::create(Sector * sector, float velocity, Node * view /*=nullptr*/)
{
	Bullet * ret = new (std::nothrow) Bullet();
	if (ret != nullptr && ret->init(sector, velocity, view))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

bool Bullet::init(Sector * sector, float velocity, Node * view)
{
	if (!Node::init())
		return false;

	this->view = view;
	view->setPosition(Vec2::ZERO);
	this->velocity = velocity;

	engine = Engine::create(sector, this);
	if (engine == nullptr)
	{
		CCLOG("Failed create engine");
		return false;
	}
	this->addComponent(engine);
	engine->setMaxMovVelocity(velocity);
	engine->edgeSectorCollisionReaction = [this](const Vec2 & pos)
	{
		this->getEngine()->setCurrMovVelocity(0.0f);
		this->setDead();
	};

	this->addChild(view, 0);

	scheduleUpdate();

	return true;
}


void Bullet::update(float dt)
{
	Node::update(dt);

	if (dead)
	{
		if (view != nullptr)
		{
			auto ps = dynamic_cast<ParticleSystem *>(view);
			if (ps != nullptr)
			{
				if (!ps->isPaused())
				{
					ps->pauseEmissions();
					return;
				}
				else if (ps->getParticleCount() > 0)
					return;
			}
		}
		runAction(RemoveSelf::create());
		return;
	}

	const Vec2 & ownpos = getPosition();
	if (attackingBulletsComponent != nullptr)
	{
		if (ownpos.distance(targetPosition) <= damageDistance)
		{
			attackingBulletsComponent->uregistrateBullet(this);
			auto target = attackingBulletsComponent->getOwner();
			//hit target and removeself
			dead = true;
			auto exp = ParticleSun::create();
			exp->setAutoRemoveOnFinish(true);
			exp->setScale(0.1f);
			exp->setDuration(0.3f);
			exp->setPosition(target->convertToNodeSpace(this->getPosition()));
			target->addChild(exp, 3);
			exp->runAction(ScaleTo::create(0.16f, 0.75f));
		}
		
	}
}

void Bullet::setTarget(Node * target)
{
	CCASSERT(target != nullptr, "Target shouldn't be null!");

	attackingBulletsComponent = dynamic_cast<AttackingBullets *>(target->getComponent(AttackingBullets::name));
	CCASSERT(attackingBulletsComponent != nullptr, "Target shouldn't be null!");
	attackingBulletsComponent->registrateBullet(this);
	this->damageDistance = attackingBulletsComponent->getRaduis();
	engine->setCurrMovVelocity(velocity);
}

void Bullet::loseTarget()
{
	attackingBulletsComponent = nullptr;
}

void Bullet::updateTargetPosition(const Vec2 & targetPos)
{
	this->targetPosition = targetPos;
	engine->turnToAngle(-CC_RADIANS_TO_DEGREES((targetPos - getPosition()).getAngle()));
}
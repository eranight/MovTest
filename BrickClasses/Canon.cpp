#include "Canon.h"
#include "Bullet.h"
#include "Sector.h"

USING_NS_CC;

using namespace AstralGame;

Canon::Canon(Sector * sector, cocos2d::Node * user, cocos2d::Vec2 position, float rechargeTime) :
sector(sector), user(user), position(position), rechargeTime(rechargeTime), rechargeTimer(rechargeTime), ready(true)
{
	CCASSERT(sector != nullptr, "Sector shouldn't be null!");
	CCASSERT(user != nullptr, "User shouldn't be null!");
}

void Canon::update(float dt)
{
	if (!ready)
	{
		if ((rechargeTimer += dt) >= rechargeTime)
		{
			ready = true;
			rechargeTimer = 0.0f;
		}
	}
}

void Canon::shot(Node * target)
{
	CCASSERT(ready, "reary is not true!");
	auto bullet = createBullet();
	if (bullet != nullptr)
		bullet->setTarget(target);
	ready = false;
}

AstralGame::Bullet * Canon::createBullet()
{
	auto ps = ParticleFire::create();
	if (ps == nullptr)
	{
		CCLOG("Bullet was not created!");
		return nullptr;
	}
	ps->setStartSize(15.0f);
	ps->setEndSize(1.0f);
	ps->setPosition(Vec2(0.0f, 0.0f));
	ps->setLife(0.3f);
	ps->setLifeVar(0.1f);
	//ps->setEndColor(Color4F::GREEN);
	ps->setTotalParticles(200);
	ps->setEmitterMode(ParticleSystem::Mode::RADIUS);
	auto bullet = Bullet::create(sector, 250.0f, ps);
	bullet->setPosition(user->convertToWorldSpace(position));
	sector->addChild(bullet, 1, "bullet");

	return bullet;
}
#include "AttackingBullets.h"
#include "Bullet.h"

USING_NS_CC;
using namespace AstralGame;

const std::string AstralGame::AttackingBullets::name = "attacking_bullet";

AttackingBullets::AttackingBullets() : radius(0.0f) {}

AttackingBullets::~AttackingBullets()
{
	resetBullets();
}

AttackingBullets * AttackingBullets::create(float radius)
{
	AttackingBullets * ret = new (std::nothrow) AttackingBullets();
	if (ret != nullptr && ret->init(radius))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

bool AttackingBullets::init(float radius)
{
	if (!Component::init())
		return false;

	this->radius = radius;

	return true;
}

void AttackingBullets::update(float dt)
{
	for (auto & bullet : bullets)
	{
		bullet->updateTargetPosition(_owner->getPosition());
	}

	//what to do when bullets are dead?

}

void AttackingBullets::registrateBullet(Bullet * bullet)
{
	bullets.push_back(bullet);
}

void AttackingBullets::uregistrateBullet(Bullet * bullet)
{
	auto iter = std::find(bullets.begin(), bullets.end(), bullet);
	if (iter != bullets.end())
		bullets.erase(iter);
}

void AttackingBullets::resetBullets()
{
	for (auto & bullet : bullets)
		bullet->loseTarget();
	bullets.clear();
}
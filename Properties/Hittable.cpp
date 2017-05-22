#include "Hittable.h"

USING_NS_CC;
using namespace AstralGame;

Hittable::Hittable(int hp) : Property(PROPS_TYPE::hittable), hp(hp) {}

Hittable * Hittable::create(int hp)
{
	auto ret = new (std::nothrow) Hittable(hp);
	if (ret != nullptr)
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

void Hittable::impactDamage(int damage)
{
	if (damage > hp)
		hp = 0;
	else
		hp -= damage;

	if (hp == 0)
	{
		CCASSERT(deadevent != nullptr, "DeadEvent shouldn't be null!");
		deadevent();
	}
		
}
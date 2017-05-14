#include "CalmBehavior.h"
#include "Engine.h"

USING_NS_CC;

using namespace AstralGame;

CalmBehavior::CalmBehavior(Engine * engine, float relaxTime, float movTime, float velocity) :
engine(engine), relaxTime(relaxTime), relaxTimer(0.0f), movTime(movTime), movTimer(0.0f), mode(1), velocity(velocity)
{
	CCASSERT(engine != nullptr, "Engine shouldn't be null!");

	engine->setCurrMovVelocity(0.0f);

	engine->edgeSectorCollisionReaction = [this](const Vec2 & nextPos)
	{
		if (this->getMode() == 2)
		{
			this->getEngine()->turnToAngle(this->getEngine()->getRotAngle() + 180.0f);
		}
	};
}

void CalmBehavior::start()
{
	mode = 1;
	engine->setCurrMovVelocity(0.0f);
	relaxTimer = 0.0f;
	movTimer = 0.0f;
}

void CalmBehavior::stop()
{

}

void CalmBehavior::update(float dt)
{
	switch (mode)
	{
	case 1:
		if ((relaxTimer += dt) >= relaxTime)
		{
			relaxTimer = 0.0f;
			mode = 2;
			engine->turnToAngle(RandomHelper::random_real(0.0f, 359.0f));
			engine->setCurrMovVelocity(velocity);
		}
		break;
	case 2:
		if ((movTimer += dt) >= movTime)
		{
			movTimer = 0.0f;
			mode = 1;
			engine->setCurrMovVelocity(0.0f);
		}
		break;
	}
}
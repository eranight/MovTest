#include "TrackingTarget.h"

USING_NS_CC;
using namespace AstralGame;

const std::string TrackingTarget::NAME = "tracking_target";

TrackingTarget * TrackingTarget::create(float trackingRadius)
{
	auto ret = new (std::nothrow) TrackingTarget();
	if (ret != nullptr && ret->init(trackingRadius))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

bool TrackingTarget::init(float trackingRadius)
{
	if (!Component::init())
		return false;

	this->setName(NAME);

	this->trackingRadius = trackingRadius;

	return true;
}

void TrackingTarget::update(float dt)
{
	Component::update(dt);
	CCASSERT(targetIsInTrakcingZoneReaction != nullptr, "targetIsInTrakcingZoneReaction shouldn't be null!");

	if (target != nullptr)
	{
		float dist = target->getPosition().distance(_owner->getPosition());
		if (dist <= trackingRadius)
			targetIsInTrakcingZoneReaction(target);
	}
}

void TrackingTarget::setTarget(Node * target)
{
	this->target = target;
}

void TrackingTarget::loseTarget()
{
	target = nullptr;
}
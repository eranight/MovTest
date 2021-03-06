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
	this->target = nullptr;
	this->trackingRadius = trackingRadius;
	this->trackingTime = 1.5f;
	this->trackingTimer = 0.0f;

	return true;
}

void TrackingTarget::update(float dt)
{
	if (!_enabled) return;
	Component::update(dt);
	CCASSERT(targetIsInTrakcingZoneReaction != nullptr, "targetIsInTrakcingZoneReaction shouldn't be null!");

	trackingTimer += dt;
	if (target != nullptr)
	{
		float dist = target->getPosition().distance(_owner->getPosition());
		if (trackingTimer >= trackingTime && dist <= trackingRadius)
			targetIsInTrakcingZoneReaction(target);
	}
	if (trackingTimer >= trackingTime)
		trackingTimer = 0.0f;
}

void TrackingTarget::setTarget(Node * target)
{
	this->target = target;
}
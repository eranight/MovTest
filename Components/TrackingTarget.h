#ifndef __TRACKINGTARGET_H__
#define __TRACKINGTARGET_H__

#include "cocos2d.h"

namespace AstralGame
{
	class Engine;

	class TrackingTarget : public cocos2d::Component
	{
	protected:

		TrackingTarget() {}

	public:

		static TrackingTarget * create(float trackingRadius);

		bool init(float trackingRadius);
		void update(float dt) override;

		static const std::string NAME;
		
		//it call when distance between owner and target is equal or small than trackingRadius
		//it shouldn't be null!
		std::function<void(cocos2d::Node *)> targetIsInTrakcingZoneReaction;
		std::function<void()> loseTargetReaction;

	public:

		cocos2d::Node * getTarget() { return target; }
		float getTrackingRadius() { return trackingRadius; }
	
		void setTarget(cocos2d::Node * target);
		void loseTarget();
	
	private:
	
		cocos2d::Node * target;
		float trackingRadius;
		float trackingTime;
		float trackingTimer;
	};
}

#endif //__TRACKINGTARGET_H__
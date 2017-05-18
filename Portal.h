#ifndef   __PORTAL_H__
#define	  __PORTAL_H__

#include "cocos2d.h"

namespace AstralGame
{
	class Portal : public cocos2d::Node
	{
	protected:

		Portal() = default;

	public:

		static Portal * create(cocos2d::Vec2 positonForTarget);

		bool init(cocos2d::Vec2 positonForTarget);

		void update(float dt) override;

		Portal * getExitPortal() { return this->exitPortal; }
		cocos2d::Node * getTarget() { return this->target; }

		void setExitPortal(Portal * exitPortal) { this->exitPortal = exitPortal; }
		void setTarget(cocos2d::Node * target) { this->target = target; }

	public:

		void movingTarget(cocos2d::Node * target);

	private:

		cocos2d::Node * view;
		cocos2d::Vec2 positonForTarget;
		Portal * exitPortal;
		cocos2d::Node * target;
	};
}

#endif  //__PORTAL_H__
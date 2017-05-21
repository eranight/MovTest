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

		bool init(const cocos2d::Vec2 & positonForTarget);

		void update(float dt) override;

	public:

		cocos2d::Node * getTarget() { return this->target; }
		void setTarget(cocos2d::Node * target) { this->target = target; }

	public:

		virtual void teleportationIn(cocos2d::Node * target);
		virtual void teleportationOut(cocos2d::Node * target);


	protected:

		cocos2d::Node * view;
		cocos2d::Vec2 positionForTarget;
		cocos2d::Node * target;
	};

	//portal teleport to another portal in the same sector
	class InnerPortal : public Portal
	{
	protected:
		
		InnerPortal() = default;

	public:

		static InnerPortal * create(const std::string & exitPortalName, cocos2d::Vec2 & positionForTarget);
		bool init(const std::string & exitPortalName, const cocos2d::Vec2 & positionForTarget);

	public:

		void teleportationIn(cocos2d::Node * target) override;

	public:

		const std::string &getExitPortalName() { return exitPortalName; }

	private:

		std::string exitPortalName;

	};

}

#endif  //__PORTAL_H__
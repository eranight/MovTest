#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "cocos2d.h"
#include <functional>

class Sector;

namespace AstralGame
{

	class Engine : public cocos2d::Component
	{
	protected:

		Engine(Sector * sector, cocos2d::Node * user, cocos2d::ParticleSystem * view = nullptr);

	public:		//common interface

		static Engine * create(Sector * sector, cocos2d::Node * user, cocos2d::ParticleSystem * view = nullptr);

		//for manage rotation, movement and view
		void update(float dt) override;

		//call it when sector->checkValidPosition(nextPos) is false
		//can be null (in this case movement will be stoped)
		std::function<void(const cocos2d::Vec2 &)> edgeSectorCollisionReaction;

	public:

		Sector * getSector() { return sector; }
		cocos2d::Node * getUser() { return user; }
		cocos2d::ParticleSystem * getView() { return view; }

		void setSector(Sector * sector) { this->sector = sector; }

	public:		//rotation interface

		float getRotVelocity() { return rotVelocity; }
		float getRotDirection() { return rotDirection; }
		float getRotAngle() { return angle; }

		void  setRotVelocity(float rotVelocity) { this->rotVelocity = rotVelocity; }
		void  setRightRotDirection() { rotDirection = 1.0f; }
		void  setLeftRotDirection()  { rotDirection = -1.0f; }
		void  resetRotDirection() { rotDirection = 0.0f; }

		void  turnToAngle(float angle);

	public:		//movement interface

		float getMaxMovVelocity()  { return maxMovVelocity; }
		float getCurrMovVelocity() { return currMovVelocity; }
		const cocos2d::Vec2 & getMovDirection() { return movDirection; }

		//currMovVelocity can't be grater maxMovVelocity
		void setMaxMovVelocity(float maxMovVelocity);
		void setCurrMovVelocity(float currMovVelocity);
		void setMovDirection(const cocos2d::Vec2 & movDirection);

	private:

		Sector * sector;

		cocos2d::Node * user;

		cocos2d::ParticleSystem * view;

	private:	//rotation implementation

		float angle; //current angle in degrees
		float rotDirection; //1.0f - cw-rotation, -1.0f - ccw-rotation
		float rotVelocity;

	private:	//movement implementation

		cocos2d::Vec2 movDirection;
		float maxMovVelocity;
		float currMovVelocity;

	};

}
#endif //__ENGINE_H__
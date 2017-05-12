#ifndef  __BULLET_H__
#define  __BULLET_H__

#include "cocos2d.h"

class Sector;

namespace AstralGame
{
	class Engine;
	class AttackingBullets;

	class Bullet : public cocos2d::Node
	{
	protected:

		Bullet();

	public:

		static Bullet * create(Sector * sector, float velocity, cocos2d::Node * view = nullptr);
		bool init(Sector * sector, float velocity, cocos2d::Node * view);
		void update(float dt) override;

	public:

		cocos2d::Node * getView() { return view; }

		Engine * getEngine() { return engine; }
		const cocos2d::Vec2 & getTargetPosition() { return targetPosition; }

		void setTarget(Node * target);
		void loseTarget();
		void updateTargetPosition(const cocos2d::Vec2 & targetPos);

	public:

		bool isDead() { return dead; }
		void setDead() { dead = true; }

	private:

		//particlesystem or sprite
		cocos2d::Node * view;
		//set in setTarget method
		AttackingBullets * attackingBulletsComponent;
		//if target is null bullet fly toward targetposition!
		cocos2d::Vec2 targetPosition;

		Engine * engine;

	private:

		float velocity;
		float damageDistance;

		bool dead;

	};
}

#endif //__BULLET_H__
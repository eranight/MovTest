#ifndef __CANON_H__
#define __CANON_H__

#include "cocos2d.h"


class Sector;

namespace AstralGame
{
	class Bullet;

	class Canon
	{
	public:

		Canon(Sector * sector, cocos2d::Node * user, cocos2d::Vec2 position, float rechargeTime);

	public:

		void update(float dt);
		bool isReady() { return ready; }

		void shot(cocos2d::Node * target);

	public:

		float getRechargeTime() { return rechargeTime; }
		const cocos2d::Vec2 & getPosition() { return position; }

	private:

		Sector * sector;
		cocos2d::Node * user;

		Bullet * createBullet();

	private:

		float rechargeTime;
		float rechargeTimer;

	private:

		bool ready;
		cocos2d::Vec2 position;

	};
}

#endif //__CANON_H__
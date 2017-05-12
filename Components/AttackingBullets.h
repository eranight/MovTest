#ifndef __ATTACKINGBULLETS_H__
#define __ATTACKINGBULLETS_H__

#include "cocos2d.h"

namespace AstralGame
{
	class Bullet;

	class AttackingBullets : public cocos2d::Component
	{
	protected:

		AttackingBullets();

	public:

		static AttackingBullets * create(float radius);

		bool init(float radius);
		void update(float dt) override;

		static const std::string name;

		~AttackingBullets();
	public:

		//пуля регистрирует и отменяет регистрацию самостоятельно в методе setTarget
		void registrateBullet(Bullet * bullet);
		void uregistrateBullet(Bullet * bullet);

		//when ship or monster becomes inaccessible call it
		void resetBullets();

		float getRaduis() { return radius; }

	private:

		std::vector<Bullet *> bullets;
		float radius;

	};
}

#endif //__ATTACKINGBULLETS_H__
#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "Property.h"

namespace AstralGame
{
	class Hittable : public Property
	{
	protected:

		Hittable(int hp);

	public:

		static Hittable * create(int hp);

	public:

		int getHp() { return hp; }
		bool isDead() { return hp == 0; }

	public:

		void impactDamage(int damage);

	private:

		int hp;

	};
}

#endif //__HITTABLE_H__
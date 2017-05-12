#ifndef  __SHIP_H__
#define  __SHIP_H__

#include "cocos2d.h"

#include "BrickClasses\Engine.h"

class Sector;

namespace AstralGame
{
	class Ship : public cocos2d::Node
	{
	protected:

		Ship();

	public:

		static Ship * create(Sector * sector);
		bool init(Sector * sector);
		void update(float dt) override;

	public:

		Engine * getEngine() { return engine; }

	private:

		cocos2d::Sprite * hall;
		Engine * engine;

	};
}

#endif //__SHIP_H__
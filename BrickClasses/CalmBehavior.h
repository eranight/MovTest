#ifndef __CALMBEHAVIOR_H__
#define __CALMBEHAVIOR_H__

#include "cocos2d.h"

namespace AstralGame
{

	class Engine;

	class CalmBehavior
	{
	public:

		//engine shouldn't be null!
		CalmBehavior(Engine * engine, float relaxTime, float movTime, float velocity);

	public:		//common interface

		void update(float dt);
		int getMode() { return mode; }
		Engine * getEngine() { return engine; }

	public:		//process interface

		void start();
		void stop();

	public: //relax-mode interface

		float getRelaxTime() { return relaxTime; }
		float getRelaxTimer() { return relaxTimer; }

	public:	//movement-mode interface

		float getMovTime() { return movTime; }
		float getMovTimer() { return movTimer; }

	public:

		float getVelocity() { return velocity; }

	private:

		Engine * engine;

		//1 - relax, 2 - movement
		int mode;

	private:

		float relaxTime;
		float relaxTimer;

	private:

		float movTime;
		float movTimer;

	private:

		float velocity;

	};

}
#endif //__CALMBEHAVIOR_H__
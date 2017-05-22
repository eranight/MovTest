#ifndef __AGRESSIVEBEHAVIOR_H__
#define __AGRESSIVEBEHAVIOR_H__

#include "cocos2d.h"

namespace AstralGame
{
	class Engine;
	class Canon;
	class Hittable;

	class AgressiveBehavior
	{
	public:

		AgressiveBehavior(Engine * engine, Canon * canon, float maxFireDistance, float minFireDistance, float velocity);

	public:		//common interface

		void update(float dt);
		int getMode() { return mode; }
		Engine * getEngine() { return engine; }
		Canon * getCanon() { return canon; }
		cocos2d::Node * getTarget() { return target; }

	public:		//process interface

		void start(cocos2d::Node * target);
		void stop();

	public:		//distance interface

		float getMinFireDistance() { return minFireDistance; }
		float getMaxFireDistance() { return maxFireDistance; }

		//change distance real-time
		void setMinFireDistance(float minFireDistance);
		void setMaxFireDistance(float maxFireDistance);

	public:

		float getVelocity() { return velocity; }
		//change velocity real-time
		void setVelocity(float velocity);

	private:

		Engine * engine;
		Canon * canon;
		cocos2d::Node * target;
		Hittable * hittable;

		//1 - reach target, 2 - fire, 3 - change position
		int mode;

	private:

		float minFireDistance;
		float maxFireDistance;

	private:

		float velocity;

	};

}
#endif //__AGRESSIVEBEHAVIOR_H__
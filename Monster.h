#ifndef  __MONSTER_H__
#define  __MONSTER_H__

#include "cocos2d.h"

#include "BrickClasses\Engine.h"
#include "BrickClasses\Canon.h"
#include "BrickClasses\CalmBehavior.h"
#include "BrickClasses\AgressiveBehavior.h"

class Sector;

namespace AstralGame
{
	class Monster : public cocos2d::Node
	{
	protected:

		Monster();

	public:

		static Monster * create(Sector * sector, float trackingDistance);

		bool init(Sector * sector, float trackingDistance);

		void update(float dt) override;

		~Monster();

	public:

		int getMode() { return behaviorMode; }
		cocos2d::Node * getTarget() { return target; }

		//if passed target is not null, Monster-class is creating AgressiveBehavior-field
		//if passed target is null Monster-class switch to calmBehavior
		void setTarget(cocos2d::Node * target = nullptr);

	public:

		Engine * getEngine() { return engine; }
		CalmBehavior * getCalmBehavior() { return calmBehavior; }
		AgressiveBehavior * getAgressiveBehavior() { return agressiveBehavior; }

	private:

		int behaviorMode; //1 - calm, 2 - agressive;
		cocos2d::Node * target; //tracking target (if distance 

	private:

		cocos2d::Sprite * body;

		//Monster-class must manage creating and deleting this fields
		Engine * engine;
		Canon * canon;
		CalmBehavior * calmBehavior;
		AgressiveBehavior * agressiveBehavior;

	private:

		float trackingDistance;

	};
}


#endif //__MONSTER_H__
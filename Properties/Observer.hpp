#ifndef  __OBSERVRER_HPP__
#define  __OBSERVRER_HPP__

#include "Property.h"

namespace AstralGame
{

	class Observer : public Property
	{
	protected:
		Observer();
		
	public:
	
		CREATE_FROM_REF(Observer);
		~Observer();
		
	public:

		void captureTarget(cocos2d::Node * target);
		void loseTarget(); //this method for Observed!!!
		void dropTarget(); //this method for Sector!!!

	public:

		std::function<void()> loseTargetReaction;

	public:

		cocos2d::Node * getTarget() { return target; }

	private:

		cocos2d::Node * target;

	};
}

#endif //__OBSERVRER_HPP__
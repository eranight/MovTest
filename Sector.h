#ifndef  __SECTOR_H__
#define  __SECTOR_H__

#include "cocos2d.h"
#include "Ship.h"

class ObjectsFactory;
class ComponentsFactory;

class Sector : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float dt) override;

	CREATE_FUNC(Sector);

	~Sector();

public: //sector math interface

	bool checkValidPosition(const cocos2d::Vec2 & pos);

public: //

	void setNodeUnobtainable(cocos2d::Node * node, bool resetBullets = true);
	void setNodeObtainable(cocos2d::Node * node);

private:

	ObjectsFactory * _objFactory;
	ComponentsFactory * _comFactory;

	bool createFactories();

	bool createPortals();

	bool createShip();

	bool createMontster();

private:

	AstralGame::Ship * ship;

	cocos2d::EventListenerKeyboard * eventListenerKeyboard;

	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _origin;

};

#endif //__SECTOR_H__
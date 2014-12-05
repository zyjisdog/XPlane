#pragma once
#include "cocos2d.h"

class About : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// a selector callback
	void menuCloseCallback(Ref* sender);

	// implement the "static node()" method manually
	CREATE_FUNC(About);

};


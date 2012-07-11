//
//  InputEventTest.h
//  TVPortable
//
//  Created by Ruiwei Bu on 7/11/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
//

#ifndef TVPortable_InputEventTest_h
#define TVPortable_InputEventTest_h

#include "cocos2d.h"

class MyInputListener: public cocos2d::CCInputListener, public cocos2d::CCNode {
public:
    MyInputListener();
    virtual ~MyInputListener();
    
    virtual bool onMouseEvent(const cocos2d::CCMouseEvent& evt);
    virtual bool onKeyEvent(const cocos2d::CCKeyEvent& evt);
    virtual bool onJoystickEvent(const cocos2d::CCJoyStickEvent& evt);
};

#endif

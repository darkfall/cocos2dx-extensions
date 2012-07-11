//
//  InputEventTest.cpp
//  TVPortable
//
//  Created by Ruiwei Bu on 7/11/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
//

#include "InputEventTest.h"

using namespace cocos2d;

MyInputListener::MyInputListener() {
    CCInputDispatcher::Instance().addListener(this, 1);
}

MyInputListener::~MyInputListener() {
    CCInputDispatcher::Instance().removeListener(this);
}

bool MyInputListener::onMouseEvent(const CCMouseEvent& evt) {
    switch(evt.state) {
        case CCMouse::Press:
            printf("mouse button %d pressed!\n", (int)evt.button);
            break;
            
        case CCMouse::Release:
            printf("mouse button %d released!\n", (int)evt.button);
            break;
            
        default:
            break;
    }
    return false;
}

bool MyInputListener::onKeyEvent(const CCKeyEvent& evt) {
    switch (evt.state) {
        case CCKey::Press:
            printf("key %c pressed!\n", evt.toCharCode());
            break;
            
        case CCKey::Release:
            printf("key %c released!\n", evt.toCharCode());
            break;
            
        default:
            break;
    }
    return false;
}

bool MyInputListener::onJoystickEvent(const CCJoyStickEvent& evt) {
    return false;
}

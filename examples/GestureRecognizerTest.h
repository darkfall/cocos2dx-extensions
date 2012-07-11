//
//  GestureRecognizerTest.h
//  TVPortable
//
//  Created by Ruiwei Bu on 7/11/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
//

#ifndef TVPortable_GestureRecognizerTest_h
#define TVPortable_GestureRecognizerTest_h

#include "cocos2d.h"
#include "extensions/CCGestureRecognizer.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

class MyGestureRecognizer: public cocos2d::CCNode, public cocos2d::CCGestureListener {
public:
    MyGestureRecognizer();
    virtual ~MyGestureRecognizer();
    
    virtual void onPinch(unsigned long which, float v, float scale, float x, float y);
    virtual void onPan(unsigned long which, float translationX, float translationY, float velocityX, float velocityY);
    virtual void onLongPress(unsigned long which);
    virtual void onSwipe(unsigned long which);
    virtual void onTap(unsigned long which);
    virtual void onRotation(unsigned long which, float rotation, float velocity);
    
private:
    unsigned long mPinchRecognizer;
    unsigned long mPanRecognizer;
    unsigned long mLongPressRecognizer;
    unsigned long mSwipeRecognizer;
    unsigned long mTapRecognizer;
    unsigned long mRotationRecognizer;
};


#endif


#endif

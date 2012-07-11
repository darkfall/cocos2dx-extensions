//
//  GestureRecognizerTest.cpp
//  TVPortable
//
//  Created by Ruiwei Bu on 7/11/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
//

#include "GestureRecognizerTest.h"

using namespace cocos2d;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

MyGestureRecognizer::MyGestureRecognizer() {
    CCGestureRecognizer::Instance().attachListener(this);
    
    mPinchRecognizer = CCGestureRecognizer::Instance().addPinchRecognizer();
    mPanRecognizer = CCGestureRecognizer::Instance().addPanRecognizer();
    mLongPressRecognizer = CCGestureRecognizer::Instance().addLongPressRecognizer();
    mSwipeRecognizer = CCGestureRecognizer::Instance().addSwipeRecognizer();
    mTapRecognizer = CCGestureRecognizer::Instance().addTapRecognizer();
    mRotationRecognizer = CCGestureRecognizer::Instance().addRotationRecognizer();
}

MyGestureRecognizer::~MyGestureRecognizer() {
    CCGestureRecognizer::Instance().removeListener(this);
    
    CCGestureRecognizer::Instance().removeRecognizer(mPinchRecognizer);
    CCGestureRecognizer::Instance().removeRecognizer(mPanRecognizer);
    CCGestureRecognizer::Instance().removeRecognizer(mLongPressRecognizer);
    CCGestureRecognizer::Instance().removeRecognizer(mSwipeRecognizer);
    CCGestureRecognizer::Instance().removeRecognizer(mTapRecognizer);
    CCGestureRecognizer::Instance().removeRecognizer(mRotationRecognizer);
}

void MyGestureRecognizer::onPinch(unsigned long which, float v, float scale, float x, float y) {
    printf("on pinch\n");
}

void MyGestureRecognizer::onPan(unsigned long which, float translationX, float translationY, float velocityX, float velocityY) {
    printf("on pan\n");
}

void MyGestureRecognizer::onLongPress(unsigned long which) {
    printf("on longpress\n");
}

void MyGestureRecognizer::onSwipe(unsigned long which) {
    printf("on swipe\n");
}

void MyGestureRecognizer::onTap(unsigned long which) {
    printf("on tap\n");
}

void MyGestureRecognizer::onRotation(unsigned long which, float rotation, float velocity) {
    printf("on rotation\n");
}


#endif
//
//  GestureRecognizer.h
//  Project LetsBattle
//
//  Created by Robert Bu on 7/9/12.
//  Copyright (c) 2012 Studio GameMaster. All rights reserved.
//

/*
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "CCGestureRecognizer.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import <UIKit/UIKit.h>

@interface GestureReceiver: NSObject {
    cocos2d::CCGestureRecognizer* parent;
}

@property (nonatomic, readwrite) cocos2d::CCGestureRecognizer* parent;

- (void)handlePinchGesture:(UIGestureRecognizer *)gestureRecognizer;
- (void)handlePanGesture:(UIGestureRecognizer *)gestureRecognizer;
- (void)handleLongPressGesture:(UIGestureRecognizer *)gestureRecognizer;
- (void)handleTapGesture:(UIGestureRecognizer *)gestureRecognizer;
- (void)handleRotationGesture:(UIGestureRecognizer *)gestureRecognizer;
- (void)handleSwipeGesture:(UIGestureRecognizer *)gestureRecognizer;

@end

@implementation GestureReceiver

@synthesize parent;

-(void)dealloc {
    [super dealloc];
}

-(void)handlePinchGesture:(UIGestureRecognizer *)gestureRecognizer {
    UIWindow* window = [[UIApplication sharedApplication] keyWindow];
    CGPoint pos = [gestureRecognizer locationInView:window.rootViewController.view];
    
    parent->onPinch((unsigned long)gestureRecognizer,
                    [(UIPinchGestureRecognizer*)gestureRecognizer velocity],
                    [(UIPinchGestureRecognizer*)gestureRecognizer scale],
                    pos.x,
                    pos.y);
}

-(void)handlePanGesture:(UIGestureRecognizer *)gestureRecognizer {
    UIWindow* window = [[UIApplication sharedApplication] keyWindow];
    CGPoint transtion = [(UIPanGestureRecognizer*)gestureRecognizer translationInView:window.rootViewController.view];
    CGPoint velocity = [(UIPanGestureRecognizer*)gestureRecognizer velocityInView:window.rootViewController.view];
    parent->onPan((unsigned long)gestureRecognizer,
                  transtion.x,
                  transtion.y,
                  velocity.x,
                  velocity.y);
}

-(void)handleTapGesture:(UIGestureRecognizer *)gestureRecognizer {
    parent->onTap((unsigned long)gestureRecognizer);
}

-(void)handleRotationGesture:(UIGestureRecognizer *)gestureRecognizer {
    parent->onRotation((unsigned long)gestureRecognizer,
                       [(UIRotationGestureRecognizer*)gestureRecognizer rotation],
                       [(UIRotationGestureRecognizer*)gestureRecognizer velocity]);
}

-(void)handleLongPressGesture:(UIGestureRecognizer *)gestureRecognizer {
    parent->onLongPress((unsigned long)gestureRecognizer);
}

-(void)handleSwipeGesture:(UIGestureRecognizer *)gestureRecognizer {
    parent->onSwipe((unsigned long)gestureRecognizer);
}

@end


namespace cocos2d {
    
    static GestureReceiver* __receiver;

    CCGestureRecognizer& CCGestureRecognizer::Instance() {
        static CCGestureRecognizer* instance = new CCGestureRecognizer;
        return *instance;
    }
    
    CCGestureRecognizer::CCGestureRecognizer() {
        __receiver = [[GestureReceiver alloc] init];
        __receiver.parent = this;
    }
    
    
    CCGestureRecognizer::~CCGestureRecognizer() { 
        
    }
    
    void CCGestureRecognizer::onPinch(unsigned long which, float v, float scale, float x, float y) {
        this->publishListenerEvent(&CCGestureListener::onPinch, which, v, scale, x, y);
    }
    
    void CCGestureRecognizer::onTap(unsigned long which) {
        this->publishListenerEvent(&CCGestureListener::onTap, which);
    }
    
    void CCGestureRecognizer::onLongPress(unsigned long which) {
        this->publishListenerEvent(&CCGestureListener::onLongPress, which);
    }
    
    void CCGestureRecognizer::onSwipe(unsigned long which) {
        this->publishListenerEvent(&CCGestureListener::onSwipe, which);
    }
    
    void CCGestureRecognizer::onPan(unsigned long which, float tranlationX, float translationY, float velocityX, float velocityY) {
        this->publishListenerEvent(&CCGestureListener::onPan, which, tranlationX, translationY, velocityX, velocityY);
    }
    
    void CCGestureRecognizer::onRotation(unsigned long which, float rotation, float velocity) {
        this->publishListenerEvent(&CCGestureListener::onRotation, which, rotation, velocity);
    }
    
    unsigned long CCGestureRecognizer::addPinchRecognizer() {
        UIPinchGestureRecognizer* pinch = [[UIPinchGestureRecognizer alloc] initWithTarget:__receiver action:@selector(handlePinchGesture:)];
        
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        [window.rootViewController.view addGestureRecognizer:pinch];
        
        mGestureRegozniers.insert(std::make_pair((unsigned long)pinch, pinch));
        return (unsigned long)pinch;
    }
    
    unsigned long CCGestureRecognizer::addTapRecognizer(int tapsRequired, int touchesRequired) {
        UITapGestureRecognizer* tap = [[UITapGestureRecognizer alloc] initWithTarget:__receiver action:@selector(handleTapGesture:)];
        
        tap.numberOfTapsRequired = tapsRequired;
        tap.numberOfTouchesRequired = touchesRequired;

        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        [window.rootViewController.view addGestureRecognizer:tap];
        
        mGestureRegozniers.insert(std::make_pair((unsigned long)tap, tap));
        return (unsigned long)tap;
    }
    
    unsigned long CCGestureRecognizer::addPanRecognizer(int minTouches, int maxTouches) {
        UIPanGestureRecognizer* pan = [[UIPanGestureRecognizer alloc] initWithTarget:__receiver action:@selector(handlePanGesture:)];
        
        pan.minimumNumberOfTouches = minTouches;
        pan.maximumNumberOfTouches = maxTouches;
        
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        [window.rootViewController.view addGestureRecognizer:pan];
        
        mGestureRegozniers.insert(std::make_pair((unsigned long)pan, pan));
        return (unsigned long)pan;
    }
    
    unsigned long CCGestureRecognizer::addRotationRecognizer() {
        UIRotationGestureRecognizer* rot = [[UIRotationGestureRecognizer alloc] initWithTarget:__receiver action:@selector(handleRotationGesture:)];
        
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        [window.rootViewController.view addGestureRecognizer:rot];
        
        mGestureRegozniers.insert(std::make_pair((unsigned long)rot, rot));
        return (unsigned long)rot;
    }
    
    unsigned long CCGestureRecognizer::addSwipeRecognizer(SwipeDirection diretion, int touchesRequired) {
        UISwipeGestureRecognizer* swipe = [[UISwipeGestureRecognizer alloc] initWithTarget:__receiver action:@selector(handleSwipeGesture:)];
        
        swipe.direction = (UISwipeGestureRecognizerDirection)diretion;
        swipe.numberOfTouchesRequired = touchesRequired;
        
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        [window.rootViewController.view addGestureRecognizer:swipe];
        
        mGestureRegozniers.insert(std::make_pair((unsigned long)swipe, swipe));
        return (unsigned long)swipe;
    }
    
    unsigned long CCGestureRecognizer::addLongPressRecognizer(float minPressDuration, int tapsRequired, int touchesRequried, float movementAllowed) {
        UILongPressGestureRecognizer* longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:__receiver action:@selector(handleLongPressGesture:)];
        
        longPress.minimumPressDuration = minPressDuration;
        longPress.numberOfTouchesRequired = touchesRequried;
        longPress.numberOfTapsRequired = tapsRequired;
        longPress.allowableMovement = movementAllowed;
        
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        [window.rootViewController.view addGestureRecognizer:longPress];
        
        mGestureRegozniers.insert(std::make_pair((unsigned long)longPress, longPress));
        return (unsigned long)longPress;

    }
    
    void CCGestureRecognizer::removeRecognizer(unsigned long which) {
        CCGestureRecognizerMap::iterator it = mGestureRegozniers.find(which);
        if(it != mGestureRegozniers.end()) {
            UIGestureRecognizer* recognizer = (UIGestureRecognizer*)it->second;
            UIWindow* window = [[UIApplication sharedApplication] keyWindow];
            [window.rootViewController.view removeGestureRecognizer:recognizer];
            [recognizer release];
            
            mGestureRegozniers.erase(it);
        }
    }
    
    void CCGestureRecognizer::removeAllRecognizers() {
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        for(CCGestureRecognizerMap::iterator it = mGestureRegozniers.begin(),
            end = mGestureRegozniers.end();
            it != end;
            ++it) {
            UIGestureRecognizer* recognizer = (UIGestureRecognizer*)it->second;
            [window.rootViewController.view removeGestureRecognizer:recognizer];
            [recognizer release];
        }
        mGestureRegozniers.clear();
    }
    
    void* CCGestureRecognizer::getRecognizerByTag(unsigned long which) const {
        CCGestureRecognizerMap::const_iterator it = mGestureRegozniers.find(which);
        if(it != mGestureRegozniers.end()) {
            return it->second;
        }
        return 0;
    }

}

#endif // CC_PLATFORM_IOS

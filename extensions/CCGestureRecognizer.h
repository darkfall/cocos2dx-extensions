//
//  GestureRecognizer.h
//  Project LetsBattle
//
//  Created by Robert Bu on 7/9/12.
//  Copyright (c) 2012 Studio GameMaster. All rights reserved.
//
/*
 Copyright (c) 2010-2011 cocos2d-x.org

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

#ifndef CCGestureRecognizer_h
#define CCGestureRecognizer_h

#include "CCPlatformConfig.h"
#include "ListenerManager.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include <map>

namespace cocos2d {
    
    class CCGestureListener {
    public:
        virtual ~CCGestureListener() { }
        
        virtual void onPinch(unsigned long which, float v, float scale, float x, float y) { }
        virtual void onPan(unsigned long which, float translationX, float translationY, float velocityX, float velocityY) { }
        virtual void onLongPress(unsigned long which) { }
        virtual void onSwipe(unsigned long which) { }
        virtual void onTap(unsigned long which) { }
        virtual void onRotation(unsigned long which, float rotation, float velocity) { }
        
    };
    
    class CCGestureRecognizerImpl;
    
    class CCGestureRecognizer: public TVPortable::ListenerManager<CCGestureListener> {
    public:
        static CCGestureRecognizer& Instance();
        
        enum SwipeDirection {
            Right = 1 << 0, /* default */
            Left  = 1 << 1,
            Up    = 1 << 2,
            Down  = 1 << 3,
        };
              
        unsigned long addPinchRecognizer();
        unsigned long addTapRecognizer(int tapsRequired = 1, int touchesRequired = 1);
        unsigned long addPanRecognizer(int minTouches = 1, int maxTouches = 5);
        unsigned long addRotationRecognizer();
        unsigned long addSwipeRecognizer(SwipeDirection direction = Right, int touchesRequired = 1);
        unsigned long addLongPressRecognizer(float minPressDuration = 0.5f /* 0.5 sec */, 
                                    int tapsRequired = 1, 
                                    int touchesRequried = 1, 
                                    float movementAllowed = 10.f /* 10 pixels */);
        
        void removeRecognizer(unsigned long which);
        void removeAllRecognizers();
        
        void* getRecognizerByTag(unsigned long which) const;
        
    public:
        /* used by listeners
         users can also call these functions to simulate a gesture */
        void onPinch(unsigned long which, float v, float scale, float x, float y);
        void onPan(unsigned long which, float translationX, float translationY, float velocityX, float velocityY);
        void onLongPress(unsigned long which);
        void onSwipe(unsigned long which);
        void onTap(unsigned long which);
        void onRotation(unsigned long which, float rotation, float velocity);
        
    protected:
        CCGestureRecognizer();
        ~CCGestureRecognizer();
        
    private:        
        CCGestureRecognizerImpl* mImpl;
    };
    
}

#endif // CC_PLATFORM_IOS


#endif

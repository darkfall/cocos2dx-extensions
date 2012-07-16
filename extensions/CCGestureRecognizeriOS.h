//
//  CCGestureRecognizerImpl.h
//  TVPortable
//
//  Created by Ruiwei Bu on 7/16/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
//

#ifndef TVPortable_CCGestureRecognizerImpl_h
#define TVPortable_CCGestureRecognizerImpl_h

#include <map>

#include "CCPlatformConfig.h"

namespace cocos2d {
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    class CCGestureRecognizer;
    
    class CCGestureRecognizerImpl {
    public:
        CCGestureRecognizerImpl(CCGestureRecognizer* parent);
        ~CCGestureRecognizerImpl();
        
        unsigned long addPinchRecognizer();
        unsigned long addTapRecognizer(int tapsRequired = 1, int touchesRequired = 1);
        unsigned long addPanRecognizer(int minTouches = 1, int maxTouches = 5);
        unsigned long addRotationRecognizer();
        unsigned long addSwipeRecognizer(int direction, int touchesRequired = 1);
        unsigned long addLongPressRecognizer(float minPressDuration = 0.5f /* 0.5 sec */, 
                                             int tapsRequired = 1, 
                                             int touchesRequried = 1, 
                                             float movementAllowed = 10.f /* 10 pixels */);
        
        void removeRecognizer(unsigned long which);
        void removeAllRecognizers();
        
        void* getRecognizerByTag(unsigned long which) const;


    private:
        typedef std::map<unsigned long, void*> GestureRecognizerMap;
        GestureRecognizerMap mGestureRegozniers;
        
        CCGestureRecognizer* mParent;
    };
    
#endif
    
}

#endif

//
//  CCInputDispatcher.h
//  TVPortable
//
//  Created by Robert Bu on 6/15/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
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

#ifndef TVPortable_CCInputDispatcher_h
#define TVPortable_CCInputDispatcher_h

#include <list>
#include "CCInputEvent.h"

namespace cocos2d {
    
    class CCInputListener;
    
    /* 
     Simple Singleton dispatcher for input events on desktop
     you should add support by yourself in platform specific codes
     */
    class CC_DLL CCInputDispatcher {
    public:
        // singleton instance
        static CCInputDispatcher& Instance(); 
        
    public:
        void addListener(CCInputListener* listener, int priority);
        void removeListener(CCInputListener* listener);
        
        void adjustPriority(int priority, CCInputListener* listener);
        
        bool listenerExists(CCInputListener* listener) const;
        
        
        void publishMouseEvent(const CCMouseEvent& evt);
        void publishKeyboardEvent(const CCKeyEvent& evt);
        void publishJoystickEvent(const CCJoyStickEvent& evt);
        
        int getKeyState(CCKey::KeyCode key);
        
    private:
        typedef std::list<CCInputListener*> ListenerList;
        ListenerList mListeners;
        
        int mKeyStates[128];
        
    protected:
        CCInputDispatcher();
        ~CCInputDispatcher();
    };
    
}


#endif

//
//  CCInputDispatcher.cpp
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

#include "CCInputDispatcher.h"
#include "CCInputListener.h"

#include <algorithm>

namespace cocos2d {
    
    CCInputDispatcher::CCInputDispatcher() {
        memset(mKeyStates, 0, sizeof(int) * 128);
    }
    
    CCInputDispatcher::~CCInputDispatcher() {
        
    }
    
    CCInputDispatcher& CCInputDispatcher::Instance() {
        static CCInputDispatcher instance;
        return instance;
    }
    
    void CCInputDispatcher::addListener(CCInputListener* listener, int priority) {
        if(listenerExists(listener)) {
            printf("Listener already exists\n");
            return;
        }
        
        listener->setPriority(priority);
        
        if(mListeners.empty())
            mListeners.push_back(listener);
        else {
            ListenerList::iterator it = mListeners.begin();
            while(it != mListeners.end()) {
                if((*it)->getPriority() < priority) {
                    mListeners.insert(it, listener);
                    break;
                }
                
                ++it;
                if(it == mListeners.end()) {
                    mListeners.push_back(listener);
                }
            }
        }
    }
    
    void CCInputDispatcher::removeListener(CCInputListener* listener) {
        ListenerList::iterator it = std::find(mListeners.begin(),
                                              mListeners.end(),
                                              listener);
        if(it != mListeners.end()) {
            mListeners.erase(it);
        }
    }
    
    void CCInputDispatcher::adjustPriority(int priortity, CCInputListener* listener) {
        ListenerList::iterator it = std::find(mListeners.begin(),
                                              mListeners.end(),
                                              listener);
        if(it != mListeners.end()) {
            mListeners.erase(it);
            
            addListener(listener, priortity);
        }
    }
    
    bool CCInputDispatcher::listenerExists(CCInputListener* listener) const {
        return (std::find(mListeners.begin(),
                          mListeners.end(),
                          listener) != mListeners.end());
    }
    
    void CCInputDispatcher::publishMouseEvent(const CCMouseEvent& mouseEvent) {
        if(mListeners.empty())
            return;
        
        ListenerList::const_iterator it = mListeners.begin();
        for(; it != mListeners.end(); ++it) {
            CCInputListener* listener = *it;
            if(listener->onMouseEvent(mouseEvent))
                break;
        }
    }
    
    void CCInputDispatcher::publishKeyboardEvent(const CCKeyEvent& evt) {
        mKeyStates[evt.key] = evt.state;

        if(mListeners.empty())
            return;
        
        ListenerList::const_iterator it = mListeners.begin();
        for(; it != mListeners.end(); ++it) {
            CCInputListener* listener = *it;
            if(listener->onKeyEvent(evt))
                break;            
        }
    }
    
    void CCInputDispatcher::publishJoystickEvent(const CCJoyStickEvent& evt) {
        
        if(mListeners.empty())
            return;
        
        ListenerList::const_iterator it = mListeners.begin();
        for(; it != mListeners.end(); ++it) {
            CCInputListener* listener = *it;
            if(listener->onJoystickEvent(evt))
                break;
        }
    }
    
    int CCInputDispatcher::getKeyState(CCKey::KeyCode key) {
        return mKeyStates[key];
    }
    
}
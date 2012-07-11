//
//  CCInputListener.h
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

#ifndef TVPortable_CCInputListener_h
#define TVPortable_CCInputListener_h

#include "CCInputEvent.h"

namespace cocos2d {
    
    /*
     Simple listener class
     */
    
    class CC_DLL CCInputListener {
    public:
        CCInputListener():mPriority(0) { }
        virtual ~CCInputListener() { }
        
        virtual bool onMouseEvent(const CCMouseEvent& evt) {
            return false;
        }
        virtual bool onKeyEvent(const CCKeyEvent& evt) { 
            return false;
        }
        virtual bool onJoystickEvent(const CCJoyStickEvent& evt) {
            return false;
        }
   
        int getPriority() const { return mPriority; }
    
    private:     
        void setPriority(int priority) { mPriority = priority; }
        friend class CCInputDispatcher;
        
        int mPriority;
    };
   
} // namespace cocos2d;

#endif

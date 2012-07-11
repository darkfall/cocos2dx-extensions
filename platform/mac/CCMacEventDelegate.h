//
//  CCMacEventDelegate.h
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

#ifndef TVPortable_CCMacEventDelegate_h
#define TVPortable_CCMacEventDelegate_h

#include "CCEventDispatcher.h"
// simple delegate that delivers events to CCInputDispatcher

@interface CCMacEventDelegate: NSObject<CCMouseEventDelegate, CCKeyboardEventDelegate, CCTouchEventDelegate> {
    
}

// CCMouseEventDelegate
-(BOOL) ccMouseDown:(NSEvent*)event;
-(BOOL) ccMouseDragged:(NSEvent*)event;
-(BOOL) ccMouseMoved:(NSEvent*)event;
-(BOOL) ccMouseUp:(NSEvent*)event;
-(BOOL) ccRightMouseDown:(NSEvent*)event;
-(BOOL) ccRightMouseDragged:(NSEvent*)event;
-(BOOL) ccRightMouseUp:(NSEvent*)event;
-(BOOL) ccOtherMouseDown:(NSEvent*)event;
-(BOOL) ccOtherMouseDragged:(NSEvent*)event;
-(BOOL) ccOtherMouseUp:(NSEvent*)event;
- (BOOL)ccScrollWheel:(NSEvent *)theEvent;
- (void)ccMouseEntered:(NSEvent *)theEvent;
- (void)ccMouseExited:(NSEvent *)theEvent;

// CCKeyboardEventDelegate
-(BOOL) ccKeyUp:(NSEvent*)event;
-(BOOL) ccKeyDown:(NSEvent*)event;
-(BOOL) ccFlagsChanged:(NSEvent*)event;

// CCTouchEventDelegate
- (BOOL)ccTouchesBeganWithEvent:(NSEvent *)event;
- (BOOL)ccTouchesMovedWithEvent:(NSEvent *)event;
- (BOOL)ccTouchesEndedWithEvent:(NSEvent *)event;
- (BOOL)ccTouchesCancelledWithEvent:(NSEvent *)event;

@end

#endif

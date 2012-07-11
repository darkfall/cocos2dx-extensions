//
//  CCMacEventDelegate.cpp
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
#import "CCMacEventDelegate.h"

#import "CCInputDispatcher.h"

using namespace cocos2d;

@implementation CCMacEventDelegate

// hack
// because i do not want this delegate to be included in other source files
static CCMacEventDelegate* delegate = [[CCMacEventDelegate alloc] init];

// mac osx keycode to cc keycode
static uint8 __key_map[128] = { 0 };

- (void)__init_key_map {
    __key_map[kVK_ANSI_A] = CCKey::A;
    __key_map[kVK_ANSI_B] = CCKey::B;
    __key_map[kVK_ANSI_C] = CCKey::C;
    __key_map[kVK_ANSI_D] = CCKey::D;
    __key_map[kVK_ANSI_E] = CCKey::E;
    __key_map[kVK_ANSI_F] = CCKey::F;
    __key_map[kVK_ANSI_G] = CCKey::G;
    __key_map[kVK_ANSI_H] = CCKey::H;
    __key_map[kVK_ANSI_I] = CCKey::I;
    __key_map[kVK_ANSI_J] = CCKey::J;
    __key_map[kVK_ANSI_K] = CCKey::K;
    __key_map[kVK_ANSI_L] = CCKey::L;
    __key_map[kVK_ANSI_M] = CCKey::M;
    __key_map[kVK_ANSI_N] = CCKey::N;
    __key_map[kVK_ANSI_O] = CCKey::O;
    __key_map[kVK_ANSI_P] = CCKey::P;
    __key_map[kVK_ANSI_Q] = CCKey::Q;
    __key_map[kVK_ANSI_R] = CCKey::R;
    __key_map[kVK_ANSI_S] = CCKey::S;
    __key_map[kVK_ANSI_T] = CCKey::T;
    __key_map[kVK_ANSI_U] = CCKey::U;
    __key_map[kVK_ANSI_V] = CCKey::V;
    __key_map[kVK_ANSI_W] = CCKey::W;
    __key_map[kVK_ANSI_X] = CCKey::X;
    __key_map[kVK_ANSI_Y] = CCKey::Y;
    __key_map[kVK_ANSI_Z] = CCKey::Z;
    
    __key_map[kVK_ANSI_1] = CCKey::Num1;
    __key_map[kVK_ANSI_2] = CCKey::Num2;
    __key_map[kVK_ANSI_3] = CCKey::Num3;
    __key_map[kVK_ANSI_4] = CCKey::Num4;
    __key_map[kVK_ANSI_5] = CCKey::Num5;
    __key_map[kVK_ANSI_6] = CCKey::Num6;
    __key_map[kVK_ANSI_7] = CCKey::Num7;
    __key_map[kVK_ANSI_8] = CCKey::Num8;
    __key_map[kVK_ANSI_9] = CCKey::Num9;
    __key_map[kVK_ANSI_0] = CCKey::Num0;
    
    __key_map[kVK_F1] = CCKey::F1;
    __key_map[kVK_F2] = CCKey::F2;
    __key_map[kVK_F3] = CCKey::F3;
    __key_map[kVK_F4] = CCKey::F4;
    __key_map[kVK_F5] = CCKey::F5;
    __key_map[kVK_F6] = CCKey::F6;
    __key_map[kVK_F7] = CCKey::F7;
    __key_map[kVK_F8] = CCKey::F8;
    __key_map[kVK_F9] = CCKey::F9;
    __key_map[kVK_F10] = CCKey::F10;
    __key_map[kVK_F11] = CCKey::F11;
    __key_map[kVK_F12] = CCKey::F12;
    
    __key_map[kVK_ANSI_Equal] = CCKey::Equals;
    __key_map[kVK_ANSI_Minus] = CCKey::Minus;
    __key_map[kVK_ANSI_Period] = CCKey::Period;
    __key_map[kVK_ANSI_Comma] = CCKey::Comma;
    __key_map[kVK_ANSI_Backslash] = CCKey::Backslash;
    __key_map[kVK_ANSI_Slash] = CCKey::Slash;
    __key_map[kVK_ANSI_Grave] = CCKey::Grave;
    __key_map[kVK_ANSI_Quote] = CCKey::Apostrophe;
    __key_map[kVK_ANSI_LeftBracket] = CCKey::LeftBracket;
    __key_map[kVK_ANSI_RightBracket] = CCKey::RightBracket;
    __key_map[kVK_ANSI_Semicolon] = CCKey::Semicolon;
    
    __key_map[kVK_Command] = CCKey::LeftWin;
    __key_map[kVK_Control] = CCKey::Ctrl;
    __key_map[kVK_Delete] = CCKey::Delete;
    __key_map[kVK_CapsLock] = CCKey::CapsLock;
    __key_map[kVK_DownArrow] = CCKey::Down;
    __key_map[kVK_UpArrow] = CCKey::Up;
    __key_map[kVK_LeftArrow] = CCKey::Left;
    __key_map[kVK_RightArrow] = CCKey::Right;
    __key_map[kVK_Shift] = CCKey::Shift;
    __key_map[kVK_Space] = CCKey::Space;
    __key_map[kVK_Tab] = CCKey::Tab;
    __key_map[kVK_PageUp] = CCKey::PageUp;
    __key_map[kVK_PageDown] = CCKey::PageDown;
    __key_map[kVK_Option] = CCKey::Alt;
    __key_map[kVK_Home] = CCKey::Home;
}

- (id)init {
    
    CCEventDispatcher* dispatcher = [CCEventDispatcher sharedDispatcher];
    [dispatcher addMouseDelegate:self priority:1];
    [dispatcher addKeyboardDelegate:self priority:1];
    [dispatcher addTouchDelegate:self priority:1];
    
    [self __init_key_map];

    [super init];
    return self;
}

-(int)translateModifiers:(NSUInteger)modifiers {
    int flag = 0;
    if(modifiers & NSControlKeyMask) {
        flag |= CCKey::FlagCtrl;
    }
    if(modifiers & NSAlternateKeyMask) {
        flag |= CCKey::FlagAlt;
    }
    if(modifiers & NSShiftKeyMask) {
        flag |= CCKey::FlagShift;
    }
    return flag;
}

-(BOOL) ccMouseDown:(NSEvent*)event {
 
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::LeftButton;
    evt.state = CCMouse::Press;
    evt.deltaX = 0;
    evt.deltaY = 0;
    evt.flag = [self translatKey:[event modifierFlags]];
        
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    
    return NO;
}

-(BOOL) ccMouseDragged:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::LeftButton;
    evt.state = CCMouse::Drag;
    evt.deltaX = [event deltaX];
    evt.deltaY = [event deltaY];
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    
    return NO;
}

-(BOOL) ccMouseMoved:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::LeftButton;
    evt.state = CCMouse::Move;
    evt.deltaX = [event deltaX];
    evt.deltaY = [event deltaY];
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

-(BOOL) ccMouseUp:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::LeftButton;
    evt.state = CCMouse::Release;
    evt.deltaX = 0;
    evt.deltaY = 0;
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

-(BOOL) ccRightMouseDown:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::RightButton;
    evt.state = CCMouse::Press;
    evt.deltaX = 0;
    evt.deltaY = 0;
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

-(BOOL) ccRightMouseDragged:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::RightButton;
    evt.state = CCMouse::Drag;
    evt.deltaX = [event deltaX];
    evt.deltaY = [event deltaY];
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

-(BOOL) ccRightMouseUp:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::RightButton;
    evt.state = CCMouse::Release;
    evt.deltaX = 0;
    evt.deltaY = 0;
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

-(BOOL) ccOtherMouseDown:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::MiddleButton;
    evt.state = CCMouse::Press;
    evt.deltaX = 0;
    evt.deltaY = 0;
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

-(BOOL) ccOtherMouseDragged:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::RightButton;
    evt.state = CCMouse::Drag;
    evt.deltaX = [event deltaX];
    evt.deltaY = [event deltaY];
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

-(BOOL) ccOtherMouseUp:(NSEvent*)event {
    CCMouseEvent evt;
    
    NSPoint pos = [event locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::MiddleButton;
    evt.state = CCMouse::Release;
    evt.deltaX = 0;
    evt.deltaY = 0;
    
    evt.flag = [self translatKey:[event modifierFlags]];
    
    evt.wheel = [event deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

- (BOOL)ccScrollWheel:(NSEvent *)theEvent {
    CCMouseEvent evt;
    
    NSPoint pos = [theEvent locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::Null;
    evt.state = CCMouse::Wheel;
    evt.deltaX = 0;
    evt.deltaY = 0;
    
    evt.flag = [self translatKey:[theEvent modifierFlags]];
    
    evt.wheel = [theEvent deltaX];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
    return NO;
}

- (void)ccMouseEntered:(NSEvent *)theEvent {
    CCMouseEvent evt;
    
    NSPoint pos = [theEvent locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::Null;
    evt.state = CCMouse::Enter;
    evt.deltaX = 0;
    evt.deltaY = 0;
    evt.wheel = 0;
    
    evt.flag = [self translatKey:[theEvent modifierFlags]];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
}

- (void)ccMouseExited:(NSEvent *)theEvent {
    CCMouseEvent evt;
    
    NSPoint pos = [theEvent locationInWindow];
    evt.x = pos.x;
    evt.y = pos.y;
    evt.button = CCMouse::Null;
    evt.state = CCMouse::Leave;
    evt.deltaX = 0;
    evt.deltaY = 0;
    evt.wheel = 0;
    
    evt.flag = [self translatKey:[theEvent modifierFlags]];
    
    CCInputDispatcher::Instance().publishMouseEvent(evt);
}

/******
 Carbon keycodes
 Cocoa also uses the same keycodes in NSEvent
 
 ****/

enum {
    kVK_ANSI_A                    = 0x00,
    kVK_ANSI_S                    = 0x01,
    kVK_ANSI_D                    = 0x02,
    kVK_ANSI_F                    = 0x03,
    kVK_ANSI_H                    = 0x04,
    kVK_ANSI_G                    = 0x05,
    kVK_ANSI_Z                    = 0x06,
    kVK_ANSI_X                    = 0x07,
    kVK_ANSI_C                    = 0x08,
    kVK_ANSI_V                    = 0x09,
    kVK_ANSI_B                    = 0x0B,
    kVK_ANSI_Q                    = 0x0C,
    kVK_ANSI_W                    = 0x0D,
    kVK_ANSI_E                    = 0x0E,
    kVK_ANSI_R                    = 0x0F,
    kVK_ANSI_Y                    = 0x10,
    kVK_ANSI_T                    = 0x11,
    kVK_ANSI_1                    = 0x12,
    kVK_ANSI_2                    = 0x13,
    kVK_ANSI_3                    = 0x14,
    kVK_ANSI_4                    = 0x15,
    kVK_ANSI_6                    = 0x16,
    kVK_ANSI_5                    = 0x17,
    kVK_ANSI_Equal                = 0x18,
    kVK_ANSI_9                    = 0x19,
    kVK_ANSI_7                    = 0x1A,
    kVK_ANSI_Minus                = 0x1B,
    kVK_ANSI_8                    = 0x1C,
    kVK_ANSI_0                    = 0x1D,
    kVK_ANSI_RightBracket         = 0x1E,
    kVK_ANSI_O                    = 0x1F,
    kVK_ANSI_U                    = 0x20,
    kVK_ANSI_LeftBracket          = 0x21,
    kVK_ANSI_I                    = 0x22,
    kVK_ANSI_P                    = 0x23,
    kVK_ANSI_L                    = 0x25,
    kVK_ANSI_J                    = 0x26,
    kVK_ANSI_Quote                = 0x27,
    kVK_ANSI_K                    = 0x28,
    kVK_ANSI_Semicolon            = 0x29,
    kVK_ANSI_Backslash            = 0x2A,
    kVK_ANSI_Comma                = 0x2B,
    kVK_ANSI_Slash                = 0x2C,
    kVK_ANSI_N                    = 0x2D,
    kVK_ANSI_M                    = 0x2E,
    kVK_ANSI_Period               = 0x2F,
    kVK_ANSI_Grave                = 0x32,
    kVK_ANSI_KeypadDecimal        = 0x41,
    kVK_ANSI_KeypadMultiply       = 0x43,
    kVK_ANSI_KeypadPlus           = 0x45,
    kVK_ANSI_KeypadClear          = 0x47,
    kVK_ANSI_KeypadDivide         = 0x4B,
    kVK_ANSI_KeypadEnter          = 0x4C,
    kVK_ANSI_KeypadMinus          = 0x4E,
    kVK_ANSI_KeypadEquals         = 0x51,
    kVK_ANSI_Keypad0              = 0x52,
    kVK_ANSI_Keypad1              = 0x53,
    kVK_ANSI_Keypad2              = 0x54,
    kVK_ANSI_Keypad3              = 0x55,
    kVK_ANSI_Keypad4              = 0x56,
    kVK_ANSI_Keypad5              = 0x57,
    kVK_ANSI_Keypad6              = 0x58,
    kVK_ANSI_Keypad7              = 0x59,
    kVK_ANSI_Keypad8              = 0x5B,
    kVK_ANSI_Keypad9              = 0x5C
};

/* keycodes for keys that are independent of keyboard layout*/
enum {
    kVK_Return                    = 0x24,
    kVK_Tab                       = 0x30,
    kVK_Space                     = 0x31,
    kVK_Delete                    = 0x33,
    kVK_Escape                    = 0x35,
    kVK_Command                   = 0x37,
    kVK_Shift                     = 0x38,
    kVK_CapsLock                  = 0x39,
    kVK_Option                    = 0x3A,
    kVK_Control                   = 0x3B,
    kVK_RightShift                = 0x3C,
    kVK_RightOption               = 0x3D,
    kVK_RightControl              = 0x3E,
    kVK_Function                  = 0x3F,
    kVK_F17                       = 0x40,
    kVK_VolumeUp                  = 0x48,
    kVK_VolumeDown                = 0x49,
    kVK_Mute                      = 0x4A,
    kVK_F18                       = 0x4F,
    kVK_F19                       = 0x50,
    kVK_F20                       = 0x5A,
    kVK_F5                        = 0x60,
    kVK_F6                        = 0x61,
    kVK_F7                        = 0x62,
    kVK_F3                        = 0x63,
    kVK_F8                        = 0x64,
    kVK_F9                        = 0x65,
    kVK_F11                       = 0x67,
    kVK_F13                       = 0x69,
    kVK_F16                       = 0x6A,
    kVK_F14                       = 0x6B,
    kVK_F10                       = 0x6D,
    kVK_F12                       = 0x6F,
    kVK_F15                       = 0x71,
    kVK_Help                      = 0x72,
    kVK_Home                      = 0x73,
    kVK_PageUp                    = 0x74,
    kVK_ForwardDelete             = 0x75,
    kVK_F4                        = 0x76,
    kVK_End                       = 0x77,
    kVK_F2                        = 0x78,
    kVK_PageDown                  = 0x79,
    kVK_F1                        = 0x7A,
    kVK_LeftArrow                 = 0x7B,
    kVK_RightArrow                = 0x7C,
    kVK_DownArrow                 = 0x7D,
    kVK_UpArrow                   = 0x7E
};

/* ISO keyboards only*/
enum {
    kVK_ISO_Section               = 0x0A
};

/* JIS keyboards only*/
enum {
    kVK_JIS_Yen                   = 0x5D,
    kVK_JIS_Underscore            = 0x5E,
    kVK_JIS_KeypadComma           = 0x5F,
    kVK_JIS_Eisu                  = 0x66,
    kVK_JIS_Kana                  = 0x68
};

/*** 
 End of keycodes
 ***/

-(int) translatKey:(unsigned short)cocoa_key {
    return __key_map[cocoa_key];
}

-(BOOL) ccKeyUp:(NSEvent*)event {
    CCKeyEvent evt;
    evt.key = (CCKey::KeyCode)[self translatKey:[event keyCode]];
    evt.flag = [self translatKey:[event modifierFlags]];
    evt.state = CCKey::Release;

    CCInputDispatcher::Instance().publishKeyboardEvent(evt);
    return NO;
}

-(BOOL) ccKeyDown:(NSEvent*)event {
    CCKeyEvent evt;
    evt.key = (CCKey::KeyCode)[self translatKey:[event keyCode]];
    evt.flag = [self translatKey:[event modifierFlags]];
    evt.state = CCKey::Press;

    CCInputDispatcher::Instance().publishKeyboardEvent(evt);
    return NO;
}

-(BOOL) ccFlagsChanged:(NSEvent*)event {
    // ?
    return NO;
}

- (BOOL)ccTouchesBeganWithEvent:(NSEvent *)event {
    
    return NO;
}

- (BOOL)ccTouchesMovedWithEvent:(NSEvent *)event {
    
    return NO;
}

- (BOOL)ccTouchesEndedWithEvent:(NSEvent *)event {
    
    return NO;
}

- (BOOL)ccTouchesCancelledWithEvent:(NSEvent *)event {
    
    return NO;
}

@end
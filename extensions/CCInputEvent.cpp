//
//  CCInputEvent.cpp
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

#include "CCInputEvent.h"

namespace cocos2d {
    
    bool CCKeyEvent::isKeyDown(CCKey::KeyCode k) const {
        return (k == this->key && state == CCKey::Press);
    }
    
    bool CCKeyEvent::isKeyUp(CCKey::KeyCode k) const {
        return (k == this->key && state == CCKey::Release);
    }
    
    bool CCKeyEvent::isDigit() const {
        return this->key >= 48 && this->key <= 57;
    }
    
    bool CCKeyEvent::isLetter() const {
        return (((this->key >= 65 && this->key <= 90)
                 || (this->key >= 97 && this->key <= 122)
                 || (this->key >= 192 && this->key <= 255))
                && (this->key != 215) && (this->key != 247));
    }
    
    char CCKeyEvent::toCharCode() const {
        if(isPrintable()) {
            return (char)key;
        }
        return '?';
    }
    
    bool CCKeyEvent::isPrintable() const {
        if((this->key >= CCKey::Num0 && key <= CCKey::Num9) ||
           (this->key >= CCKey::A && key <= CCKey::Z) ||
           (this->key == CCKey::Grave) ||
           (this->key == CCKey::Minus) ||
           (this->key == CCKey::Equals) ||
           (this->key == CCKey::Backslash) ||
           (this->key == CCKey::LeftBracket) ||
           (this->key == CCKey::RightBracket) ||
           (this->key == CCKey::Semicolon) ||
           (this->key == CCKey::Apostrophe) ||
           (this->key == CCKey::Comma) ||
           (this->key == CCKey::Period) ||
           (this->key == CCKey::Slash) ||
           (this->key == CCKey::Space)
           )
            return true;
        return false;
    }
    
    bool CCKeyEvent::isShiftFlag() const {
        return this->flag & CCKey::FlagShift;
    }
    
    bool CCKeyEvent::isCtrlFlag() const {
        return this->flag & CCKey::FlagCtrl;
    }
    
    bool CCKeyEvent::isAltFlag() const {
        return this->flag & CCKey::FlagAlt;
    }
    
}
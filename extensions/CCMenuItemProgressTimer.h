//
//  Header.h
//  TVPortable
//
//  Created by Ruiwei Bu on 7/12/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
//

#ifndef TVPortable_Header_h
#define TVPortable_Header_h

#include "CCMenuItem.h"
#include "CCProgressTimer.h"

namespace cocos2d {
    
    class CCMenuItemProgressTimer: public CCMenuItem, public CCRGBAProtocol {
        CC_PROPERTY(CCProgressTimer*, mProgressTimer, ProgressTimer);
        CC_PROPERTY(CCSprite*, mNormalImage, NormalImage);
        CC_PROPERTY(CCSprite*, mMaskImage, MaskImage);
        CC_PROPERTY(CCSprite*, mDisabledImage, DisabledImage);
        
    public:
        CCMenuItemProgressTimer();
        virtual ~CCMenuItemProgressTimer();
        
    public:
        static CCMenuItemProgressTimer* itemFromSpriteAndTime(CCSprite* mask, CCSprite* normalSprite, float interval, CCProgressTimerType type, CCSprite* disabledSprite = NULL);

        static CCMenuItemProgressTimer* itemFromSpriteAndTime(CCSprite* mask, CCSprite* normalSprite, float interval, CCProgressTimerType type, SelectorProtocol* target, SEL_MenuHandler selector);
        
        static CCMenuItemProgressTimer* itemFromSpriteAndTime(CCSprite* mask, CCSprite* normalSprite, CCSprite* disabledSprite, float interval, CCProgressTimerType type, SelectorProtocol* target, SEL_MenuHandler selector);

    public:
                                                              
        // super methods
        virtual void setColor(const ccColor3B& color);
        virtual const ccColor3B& getColor();
        virtual void setOpacity(GLubyte opacity);
        virtual GLubyte getOpacity();
        virtual void setIsOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
        virtual bool getIsOpacityModifyRGB(void) { return false;}
        
        virtual void activate();
        virtual void selected();
        virtual void unselected();
        virtual void setIsEnabled(bool bEnabled);
        
    protected:
        
        bool init(CCSprite* mask, CCSprite* normalSprite, CCSprite* disabledSprite, float interval, CCProgressTimerType type, SelectorProtocol* target, SEL_MenuHandler selector);
        
        float mInterval;
        float mCurrent;
        bool  mCanBeActivated;
        CCProgressTimerType mType;
        
        void onTimerTick(float dt);
        
    };
    
}

#endif

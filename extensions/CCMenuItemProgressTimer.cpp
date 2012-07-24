//
//  CCMenuItemProgressTimer.cpp
//  TVPortable
//
//  Created by Ruiwei Bu on 7/12/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
//

#include "CCMenuItemProgressTimer.h"
#include "CCDirector.h"
#include "CCPointExtension.h"
#include "CCTextureCache.h"

namespace cocos2d {
    
    CCMenuItemProgressTimer::CCMenuItemProgressTimer():
    mInterval(0),
    mNormalImage(0),
    mDisabledImage(0),
    mCurrent(0),
    mCanBeActivated(true),
    mProgressTimer(0),
    mType(kCCProgressTimerTypeVerticalBarBT) {
        
    }
    
    CCMenuItemProgressTimer::~CCMenuItemProgressTimer() {
        
    }
    
    CCSprite* CCMenuItemProgressTimer::getNormalImage() {
        return mNormalImage;
    }
    
    const unsigned int	kNormalTag = 0x1;
    const unsigned int	kDisableTag = 0x2;
    
    void CCMenuItemProgressTimer::setNormalImage(CCSprite* image) {        
        if (image) {
            addChild(image, 0, kNormalTag);
            image->setAnchorPoint(ccp(0, 0));
            image->setIsVisible(true);
        }
        
        if (mNormalImage) {
            removeChild(mNormalImage, true);
        }
        
        mNormalImage = image;
    }
    
    CCSprite* CCMenuItemProgressTimer::getDisabledImage() {
        return mDisabledImage;
    }
    
    void CCMenuItemProgressTimer::setDisabledImage(CCSprite* image) {        
        if (image) {
            addChild(image, 0, kDisableTag);
            image->setAnchorPoint(ccp(0, 0));
            image->setIsVisible(true);
        }
        
        if (mDisabledImage) {
            removeChild(mDisabledImage, true);
        }
        
        mDisabledImage = image;
    }
    
    void CCMenuItemProgressTimer::setMaskImage(CCSprite* image) {
        mMaskImage = image;
        mProgressTimer->setSprite(mMaskImage);
    }
    
    CCSprite* CCMenuItemProgressTimer::getMaskImage() {
        return mMaskImage;
    }
    
    CCProgressTimer* CCMenuItemProgressTimer::getProgressTimer() {
        return mProgressTimer;
    }
    
    void CCMenuItemProgressTimer::setProgressTimer(CCProgressTimer* timer) {
        if(mProgressTimer)
            removeChild(mProgressTimer, true);
        mProgressTimer = timer;
        this->addChild(mProgressTimer);
        
        mProgressTimer->setSprite(mNormalImage);
        mProgressTimer->setPercentage(0);
        mProgressTimer->setType(mType);
    }
    
    CCMenuItemProgressTimer* CCMenuItemProgressTimer::itemFromSpriteAndTime(CCSprite* mask, CCSprite* normalSprite, float interval, CCProgressTimerType type, CCSprite* disabledSprite) {
        CCMenuItemProgressTimer* ptimer = new CCMenuItemProgressTimer();
        if(ptimer->init(mask, normalSprite, 0, interval, type, 0, 0)) {
            ptimer->autorelease();
            return ptimer;
        }
        delete ptimer;
        return 0;
    }
    
    CCMenuItemProgressTimer* CCMenuItemProgressTimer::itemFromSpriteAndTime(CCSprite* mask, CCSprite* normalSprite, float interval, CCProgressTimerType type, SelectorProtocol* target, SEL_MenuHandler selector) {
        CCMenuItemProgressTimer* ptimer = new CCMenuItemProgressTimer();
        if(ptimer->init(mask, normalSprite, 0, interval, type, target, selector)) {
            ptimer->autorelease();
            return ptimer;
        }
        delete ptimer;
        return 0;
    }
    
    CCMenuItemProgressTimer* CCMenuItemProgressTimer::itemFromSpriteAndTime(CCSprite* mask, CCSprite* normalSprite, CCSprite* disabledSprite, float interval, CCProgressTimerType type, SelectorProtocol* target, SEL_MenuHandler selector) {
        CCMenuItemProgressTimer* ptimer = new CCMenuItemProgressTimer();
        if(ptimer->init(mask, normalSprite, disabledSprite, interval, type, target, selector)) {
            ptimer->autorelease();
            return ptimer;
        }
        delete ptimer;
        return 0;
    }
    
    bool CCMenuItemProgressTimer::init(CCSprite* mask, CCSprite* normalSprite, CCSprite* disabledSprite, float interval, CCProgressTimerType type, SelectorProtocol* target, SEL_MenuHandler selector) {
        assert(normalSprite);
        
        CCMenuItem::initWithTarget(target, selector);
        
        setNormalImage(normalSprite);
        setDisabledImage(disabledSprite);
        
        mProgressTimer = new CCProgressTimer();
        mInterval = interval;
        setMaskImage(mask);
        mProgressTimer->setType(type);
        
        mProgressTimer->setPercentage(0);
        
        this->addChild(mProgressTimer);
        
        mType = type;
        
        this->setContentSize(normalSprite->getContentSize());

        return true;
    }
    
    void CCMenuItemProgressTimer::setColor(const ccColor3B& color) {
        dynamic_cast<CCRGBAProtocol*>(mNormalImage)->setColor(color);
        
        if (mDisabledImage)
        {
            dynamic_cast<CCRGBAProtocol*>(mDisabledImage)->setColor(color);
        }

    }
    
    const ccColor3B& CCMenuItemProgressTimer::getColor() {
        return dynamic_cast<CCRGBAProtocol*>(mNormalImage)->getColor();

    }
    
    void CCMenuItemProgressTimer::setOpacity(GLubyte opacity) {
        dynamic_cast<CCRGBAProtocol*>(mNormalImage)->setOpacity(opacity);
        
        if (mDisabledImage)
        {
            dynamic_cast<CCRGBAProtocol*>(mDisabledImage)->setOpacity(opacity);
        }    
    }
    
    GLubyte CCMenuItemProgressTimer::getOpacity() {
        return dynamic_cast<CCRGBAProtocol*>(mNormalImage)->getOpacity();
    }
    
    void CCMenuItemProgressTimer::activate() {
        if(mCanBeActivated) {
            mProgressTimer->setPercentage(100);
            
            mCurrent = 0.f;
            mCanBeActivated = false;
            
            this->schedule(schedule_selector(CCMenuItemProgressTimer::onTimerTick),
                           CCDirector::sharedDirector()->getAnimationInterval());
            CCMenuItem::activate();
        }
    }
    
    void CCMenuItemProgressTimer::preventTimer() {
        this->unschedule(schedule_selector(CCMenuItemProgressTimer::onTimerTick));
        
        mCurrent = 0.f;
        mCanBeActivated = true;
        mProgressTimer->setPercentage(0);
    }
    
    void CCMenuItemProgressTimer::selected() {
        CCMenuItem::selected();
    }
    
    void CCMenuItemProgressTimer::unselected() {
        CCMenuItem::unselected();
    }
    
    void CCMenuItemProgressTimer::setIsEnabled(bool bEnabled) {
        CCMenuItem::setIsEnabled(bEnabled);
        
        if(!bEnabled) {
            mProgressTimer->setIsVisible(false);
        } else {
            mProgressTimer->setIsVisible(true);
        }
        
        if (bEnabled)
        {
            mNormalImage->setIsVisible(true);
            
            if (mDisabledImage)
            {
                mDisabledImage->setIsVisible(false);
            }
        }
        else
        {
            if (mDisabledImage)
            {
                mDisabledImage->setIsVisible(true);
                mNormalImage->setIsVisible(false);
            }
            else
            {
                mNormalImage->setIsVisible(true);
            }
        }
    }
    
    void CCMenuItemProgressTimer::onTimerTick(float dt) {
        mCurrent += dt;
        if(mCurrent >= mInterval) {
            this->unschedule(schedule_selector(CCMenuItemProgressTimer::onTimerTick));
            mCanBeActivated = true;
        }
        mProgressTimer->setPercentage((1.f - mCurrent / mInterval) * 100.f);
    }
}

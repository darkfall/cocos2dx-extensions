#include "CCGestureRecognizer.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "CCGestureRecognizeriOS.h"
#endif

namespace cocos2d {

    CCGestureRecognizer& CCGestureRecognizer::Instance() {
        static CCGestureRecognizer* instance = new CCGestureRecognizer;
        return *instance;
    }
    
    CCGestureRecognizer::CCGestureRecognizer() {
        mImpl = new CCGestureRecognizerImpl(this);
    }
    
    CCGestureRecognizer::~CCGestureRecognizer() { 
        
    }
    
    void CCGestureRecognizer::onPinch(unsigned long which, float v, float scale, float x, float y) {
        this->publishListenerEvent(&CCGestureListener::onPinch, which, v, scale, x, y);
    }
    
    void CCGestureRecognizer::onTap(unsigned long which) {
        this->publishListenerEvent(&CCGestureListener::onTap, which);
    }
    
    void CCGestureRecognizer::onLongPress(unsigned long which) {
        this->publishListenerEvent(&CCGestureListener::onLongPress, which);
    }
    
    void CCGestureRecognizer::onSwipe(unsigned long which) {
        this->publishListenerEvent(&CCGestureListener::onSwipe, which);
    }
    
    void CCGestureRecognizer::onPan(unsigned long which, float tranlationX, float translationY, float velocityX, float velocityY) {
        this->publishListenerEvent(&CCGestureListener::onPan, which, tranlationX, translationY, velocityX, velocityY);
    }
    
    void CCGestureRecognizer::onRotation(unsigned long which, float rotation, float velocity) {
        this->publishListenerEvent(&CCGestureListener::onRotation, which, rotation, velocity);
    }
    
    unsigned long CCGestureRecognizer::addPinchRecognizer() {
        return mImpl->addPinchRecognizer();
    }
    
    unsigned long CCGestureRecognizer::addTapRecognizer(int tapsRequired, int touchesRequired) {
        return mImpl->addTapRecognizer(tapsRequired, touchesRequired);
    }
    
    unsigned long CCGestureRecognizer::addPanRecognizer(int minTouches, int maxTouches) {
        return mImpl->addPanRecognizer(minTouches, maxTouches);
    }
    
    unsigned long CCGestureRecognizer::addRotationRecognizer() {
        return mImpl->addRotationRecognizer();
    }
    
    unsigned long CCGestureRecognizer::addSwipeRecognizer(SwipeDirection diretion, int touchesRequired) {
        return mImpl->addSwipeRecognizer(diretion, touchesRequired);
    }
    
    unsigned long CCGestureRecognizer::addLongPressRecognizer(float minPressDuration, int tapsRequired, int touchesRequried, float movementAllowed) {
        return mImpl->addLongPressRecognizer(minPressDuration, tapsRequired, touchesRequried, movementAllowed);
    }
    
    void CCGestureRecognizer::removeRecognizer(unsigned long which) {
        mImpl->removeRecognizer(which);
    }
    
    void CCGestureRecognizer::removeAllRecognizers() {
        mImpl->removeAllRecognizers();
    }
    
    void* CCGestureRecognizer::getRecognizerByTag(unsigned long which) const {
        return mImpl->getRecognizerByTag(which);
    }

}
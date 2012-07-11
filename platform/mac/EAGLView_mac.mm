/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * Idea of subclassing NSOpenGLView was taken from  "TextureUpload" Apple's sample
 */

// Only compile this code on Mac. These files should not be included on your iOS project.
// But in case they are included, it won't be compiled.
#import <Availability.h>

#import "EAGLView_mac.h"
#import <OpenGL/gl.h>
#import "CCDirectorMac.h"
#import "ccConfig.h"
#import "CCSet.h"
#import "CCTouch.h"
#import "CCIMEDispatcher.h"
#import "CCEventDispatcher.h"


#define MAX_TOUCHES     11

//USING_NS_CC;
static EAGLView *view;
static cocos2d::CCTouch *s_pTouches[MAX_TOUCHES];

@implementation EAGLView

@synthesize eventDelegate = eventDelegate_;
@synthesize indexBitsUsed;
@synthesize touchesIntergerDict;

+(void) load_
{
	NSLog(@"%@ loaded", self);
}

+(id) sharedEGLView
{
	return view;
}

- (id) initWithFrame:(NSRect)frameRect
{
	self = [self initWithFrame:frameRect shareContext:nil];
	return self;
}

- (id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context
{
    NSOpenGLPixelFormatAttribute attribs[] =
    {
		NSOpenGLPFAAccelerated,
		NSOpenGLPFANoRecovery,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, 24,
		
		0
    };
	
	NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
	
	if (!pixelFormat)
		NSLog(@"No OpenGL pixel format");
	
	if( (self = [super initWithFrame:frameRect pixelFormat:[pixelFormat autorelease]]) ) {
		
		if( context )
			[self setOpenGLContext:context];

		// Synchronize buffer swaps with vertical refresh rate
		GLint swapInt = 1;
		[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; 
		
//             GLint order = -1;
//             [[self openGLContext] setValues:&order forParameter:NSOpenGLCPSurfaceOrder];
		
		// event delegate;	
        eventDelegate_ = [CCEventDispatcher sharedDispatcher];
	}
	
	touchesIntergerDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 4, NULL, NULL);
	indexBitsUsed = 0x00000000;
	
	view = self;
	return self;
}

-(int) getUnUsedIndex
{
    int i;
    int temp = indexBitsUsed;
    
    for (i = 0; i < MAX_TOUCHES; i++) {
        if (! (temp & 0x00000001)) {
            indexBitsUsed |= (1 <<  i);
            return i;
        }
        
        temp >>= 1;
    }
    
    // all bits are used
    return -1;
}

-(void) removeUsedIndexBit:(int) index
{
	if (index < 0 || index >= MAX_TOUCHES) {
		return;
	}
    
    unsigned int temp = 1 << index;
    temp = ~temp;
    indexBitsUsed &= temp;
}
	
-(int) getWidth
{
	NSSize bound = [self bounds].size;
	return bound.width;
}

-(int) getHeight
{
	NSSize bound = [self bounds].size;
	return bound.height;
}

-(void) swapBuffers
{
}

- (void) reshape
{
	// We draw on a secondary thread through the display link
	// When resizing the view, -reshape is called automatically on the main thread
	// Add a mutex around to avoid the threads accessing the context simultaneously when resizing
	CGLLockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
	
	NSRect rect = [self bounds];
	
	cocos2d::CCDirector *director = cocos2d::CCDirector::sharedDirector();
	CGSize size = NSSizeToCGSize(rect.size);
	cocos2d::CCSize ccsize = cocos2d::CCSizeMake(size.width, size.height);
	director->reshapeProjection(ccsize);
	
	// avoid flicker
	director->drawScene();
//	[self setNeedsDisplay:YES];
	
	CGLUnlockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
}

- (void) dealloc
{	
	CFRelease(touchesIntergerDict);
	[super dealloc];
}

#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
#define DISPATCH_EVENT(__event__, __selector__) [eventDelegate_ queueEvent:__event__ selector:__selector__];
#else
#define DISPATCH_EVENT(__event__, __selector__)												\
	id obj = eventDelegate_;																\
	[obj performSelector:__selector__														\
			onThread:[(CCDirectorMac*)[CCDirector sharedDirector] runningThread]			\
		  withObject:__event__																\
	   waitUntilDone:NO];
#endif

#pragma mark EAGLView - Mouse events

- (void)mouseDown:(NSEvent *)theEvent
{
#if 1
	DISPATCH_EVENT(theEvent, _cmd);
#else
	cocos2d::CCSet set;
    cocos2d::CCTouch *pTouch;

	NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, [NSNumber numberWithInt:11]);
	int unUsedIndex = 0;
	
	// it is a new touch
	if (! index) {
		unUsedIndex = [self getUnUsedIndex];
		
		// The touches is more than MAX_TOUCHES ?
		if (unUsedIndex == -1) {
			return;
		}
		
		pTouch = s_pTouches[unUsedIndex] = new cocos2d::CCTouch();
	}
	
	NSPoint event_location = [theEvent locationInWindow];
	NSPoint local_point = [self convertPoint:event_location fromView:nil];
	
	float x = local_point.x;
	float y = [self getHeight] - local_point.y;
	pTouch->SetTouchInfo(x, y);
	
	CFDictionaryAddValue(touchesIntergerDict, [NSNumber numberWithInt:11], [NSNumber numberWithInt:unUsedIndex]);
	
	set.addObject(pTouch);
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesBegan(&set);
#endif
}

- (void)mouseMoved:(NSEvent *)theEvent
{
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
#if 1
	DISPATCH_EVENT(theEvent, _cmd);
#else
	cocos2d::CCSet set;
	
	NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, [NSNumber numberWithInt:11]);
	if (! index) {
		// if the index doesn't exist, it is an error
		return;
	}
	
	cocos2d::CCTouch *pTouch = s_pTouches[[index intValue]];
	if (! pTouch) {
		// if the pTouch is null, it is an error
		return;
	}
	
	NSPoint event_location = [theEvent locationInWindow];
	NSPoint local_point = [self convertPoint:event_location fromView:nil];
	
	float x = local_point.x;
	float y = [self getHeight] - local_point.y;
	pTouch->SetTouchInfo(x, y);
	
	set.addObject(pTouch);
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesMoved(&set);	
#endif
}

- (void)mouseUp:(NSEvent *)theEvent
{
#if 1
	DISPATCH_EVENT(theEvent, _cmd);
#else
	cocos2d::CCSet set;
	
	NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, [NSNumber numberWithInt:11]);
	if (! index) {
		// if the index doesn't exist, it is an error
		return;
	}
	
	cocos2d::CCTouch *pTouch = s_pTouches[[index intValue]];
	if (! pTouch) {
		// if the pTouch is null, it is an error
		return;
	}
	
	NSPoint event_location = [theEvent locationInWindow];
	NSPoint local_point = [self convertPoint:event_location fromView:nil];
	
	float x = local_point.x;
	float y = [self getHeight] - local_point.y;
	pTouch->SetTouchInfo(x, y);
	
	set.addObject(pTouch);
	CFDictionaryRemoveValue(touchesIntergerDict, [NSNumber numberWithInt:11]);
	s_pTouches[[index intValue]] = NULL;
	[self removeUsedIndexBit:[index intValue]];
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesEnded(&set);
	cocos2d::CCSetIterator iter = set.begin();
	for(; iter != set.end(); iter++)
	{
		cocos2d::CCTouch* pTouch = (cocos2d::CCTouch*)(*iter);
		pTouch->release();
	}	
#endif
}

- (void)rightMouseDown:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)rightMouseDragged:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)rightMouseUp:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)otherMouseDown:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)otherMouseDragged:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)otherMouseUp:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)mouseEntered:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)mouseExited:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}

-(void) scrollWheel:(NSEvent *)theEvent {
	DISPATCH_EVENT(theEvent, _cmd);
}


#pragma mark EAGLView - Key events

-(BOOL) becomeFirstResponder
{
	return YES;
}

-(BOOL) acceptsFirstResponder
{
	return YES;
}

-(BOOL) resignFirstResponder
{
	return YES;
}

- (void)keyDown:(NSEvent *)theEvent
{
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)keyUp:(NSEvent *)theEvent
{
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)flagsChanged:(NSEvent *)theEvent
{
	DISPATCH_EVENT(theEvent, _cmd);
}

#pragma mark EAGLView - Touch events
- (void)touchesBeganWithEvent:(NSEvent *)theEvent
{
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)touchesMovedWithEvent:(NSEvent *)theEvent
{
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)touchesEndedWithEvent:(NSEvent *)theEvent
{
	DISPATCH_EVENT(theEvent, _cmd);
}

- (void)touchesCancelledWithEvent:(NSEvent *)theEvent
{
	DISPATCH_EVENT(theEvent, _cmd);
}
@end

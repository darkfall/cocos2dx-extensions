#Cocos2dx-Extensions

Here are some cocos2dx extensions I wrote/modified during the development of my recent projects

###Keyboard & Mouse Events on Destop Platforms(Mac OS X and Windows)

	* CCInputEvent:		Represents keyboard / mouse / joystick events(not completed)
	* CCInputDispatcher:	Singleton that works with platform implementations to dispatch input events(modified platform sources required, see platform folder, cocos2dx-mac from http://www.cocos2d-x.org/boards/6/topics/10352)
	* CCInputListener:	Input event listener, inherit from this class and add self to CCInputDispatcher to receive input events


###Mutable CCTexture2D and CCRenderTexture

	* CCTexture2DMutable:		Created by Lam Hoang Pham, improved by Manuel Martinez-Almeida and slightly modified by me for some extensions and work with CCRenderTextureMutable
	* CCRenderTextureMutable:	A CCRenderTexture that uses CCTexture2DMutable to render, so you can modified the rendered texture(for posteffects etc)


###Gesture Recognizers for iOS
	
	* CCGestureRecognizer:	Singleton that manages UIGestureRecognizers
	* CCGestureLister:	Gesture event listener, inherit from this class and add self to CCGestureRecognizer to receive gesture events

Note: To support Gesture Recognizers, you need to add 

	window.rootViewController = viewController
	
in your AppController.mm manually

###CCMenuItemProgressTimer

	* CCMenuItemProgressTimer: CCMenuItem with a progress timer mask. Useful for skill button will cooldown.
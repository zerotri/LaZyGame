//
//  LazyGameView.h
//  LaZyEdit
//
//  Created by Wynter Woods on 1/31/13.
//  Copyright (c) 2013 Wynter Woods. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface LazyGameView : NSOpenGLView<NSWindowDelegate>
{
	double timeOfLastFrame;
	//	- (void)keyDown:(NSEvent *)theEvent
}
// OpenGL Functions
- (int) initOpenGL;
- (int) shutdownOpenGL;
- (int) reshapeOpenGLView;
- (int) updateOpenGLView;

// Game Functions
- (int) initGame;
- (int) runGame;
- (int) pauseGame;
- (int) shutdownGame;
- (int) updateGame;
@end

//
//  LazyGameView.m
//  LaZyEdit
//
//  Created by Wynter Woods on 1/31/13.
//  Copyright (c) 2013 Wynter Woods. All rights reserved.
//
#import "LazyGameView.h"
#include <lazy/platforms/osx/LazyGraphicsDevice_Cocoa.h>
#include "glm/glm.hpp"
#include <OpenGL/OpenGL.h>
#include <chrono>

static NSTimer *timer = nil;

// This will identify our vertex buffer
GLuint vertexbuffer;

@implementation LazyGameView

- (id)initWithFrame:(NSRect)frame
{
	
	//std::chrono::high_resolution_clock::time_point clock = std::chrono::high_resolution_clock::now();
	//timeOfLastFrame = clock.;
    self = [super initWithFrame:frame];
    if (self) {
    }
    
    return self;
}

- (void)windowDidResignMain:(NSNotification *)notification {
	//    NSLog(@"window did resign main");
    [timer invalidate];
    
    //game_deactivate();      // freeze, pause
    [self setNeedsDisplay:YES];
}

- (void)windowDidBecomeMain:(NSNotification *)notification {
	//    NSLog(@"window did become main");
    
    //game_activate();
    [self setNeedsDisplay:YES];
    
    timer = [NSTimer timerWithTimeInterval:1.0f/60.0f
									target:self
								  selector:@selector(timerEvent:)
								  userInfo:nil
								   repeats:YES];
    
    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
}
- (void)prepareOpenGL {
    [self initOpenGL];
    [self runGame];
}

- (void)drawRect:(NSRect)dirtyRect {
    [self updateOpenGLView];
}

- (void)reshape {
    [self reshapeOpenGLView];
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)keyDown:(NSEvent *)theEvent {
    if ([theEvent isARepeat])
        return;
    
    NSString *str = [theEvent charactersIgnoringModifiers];
    unichar c = [str characterAtIndex:0];
    
    if (c < ' ' || c > '~')     // only ASCII please
        c = 0;
    
    //key_down([theEvent keyCode], c);
}

- (void)keyUp:(NSEvent *)theEvent {
    //key_up([theEvent keyCode]);
}
- (void)timerEvent:(NSTimer *)t {
	
    [self updateGame];
    [self setNeedsDisplay:YES];
}

/*** OpenGL and Game Functionality ***/



// OpenGL Functions
- (int) initOpenGL{
    // this sets swap interval for double buffering
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    // this enables alpha in the frame buffer (commented now)
	//  GLint opaque = 0;
	//  [[self openGLContext] setValues:&opaque forParameter:NSOpenGLCPSurfaceOpacity];
	
	
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	
	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);
	
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	return 0;
}
- (int) shutdownOpenGL{
	return 0;
}
- (int) reshapeOpenGLView{
    // here I cast floats to ints; most systems use integer coordinate systems
	//  NSLog(@"view reshape {%.02f %.02f}", [self frame].size.width, [self frame].size.height);
    
    // window resize; width and height are in pixel coordinates
    // but they are floats
    float screen_w = [self frame].size.width;
    float screen_h = [self frame].size.height;
	glViewport(0, 0, screen_w, screen_h);
	
	return 0;
}
- (int) updateOpenGLView{
	glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
	
	glColor3f(1.0f, 0.85f, 0.35f);
    /*glBegin(GL_TRIANGLES);
    {
        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);
    }
    glEnd();*/
    //draw_screen();
	
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
						  0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
						  3,                  // size
						  GL_FLOAT,           // type
						  GL_FALSE,           // normalized?
						  0,                  // stride
						  (void*)0            // array buffer offset
						  );
	
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	
	glDisableVertexAttribArray(0);
    
	//  glFlush();
	// the correct way to do double buffering on Mac is this:
    [[self openGLContext] flushBuffer];
    
    int err;
    if ((err = glGetError()) != 0)
        NSLog(@"glGetError(): %d", err);

	return 0;
}

// Game Functions
- (int) initGame{
	return 0;
}
- (int) runGame{
	return 0;
}
- (int) pauseGame{
	return 0;
}
- (int) shutdownGame{
	return 0;
}
- (int) updateGame{
	return 0;
}
@end

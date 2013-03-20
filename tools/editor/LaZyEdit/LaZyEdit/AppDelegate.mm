//
//  AppDelegate.m
//  Test
//
//  Created by Wynter Woods on 1/31/13.
//  Copyright (c) 2013 Wynter Woods. All rights reserved.
//

#import "AppDelegate.h"
#import "LazyGameView.h"

@implementation AppDelegate

@synthesize window=window_, gameView=gameView_;

- (void)dealloc
{
    [super dealloc];
}
- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication *) theApplication
{
	return YES;
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	// Insert code here to initialize your application
	
	/*director = (CCDirectorMac*) [CCDirector sharedDirector];
	
	[director setView: glView_];
	[director setDisplayStats:YES];
	[director setResizeMode:kCCDirectorResize_AutoScale];
	printf("AppDelegate: applicationDidFinishLaunching\n");
	[director runWithScene: [LazyGameSceneLayer scene]];*/
}
- (IBAction)togglePlayState:(id)sender {
	//[director pause];
}
- (IBAction)toggleFullScreen: (id)sender
{
	//[director setFullScreen: ! [director isFullScreen] ];
}
@end

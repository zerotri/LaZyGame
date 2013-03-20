//
//  AppDelegate.h
//  LaZyEdit
//
//  Created by Wynter Woods on 1/31/13.
//  Copyright (c) 2013 Wynter Woods. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LazyGameView.h"

@interface AppDelegate : NSObject {
	NSWindow *window_;
	LazyGameView *gameView_;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet LazyGameView *gameView;

- (IBAction)toggleFullScreen:(id)sender;
- (IBAction)togglePlayState:(id)sender;
@end

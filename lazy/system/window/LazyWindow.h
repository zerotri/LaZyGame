//
//  LazyWindow.h
//  LaZyGame
//
//  Created by Wynter Woods on 7/11/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//
#include <lazy/LazyConfig.h>
#ifdef PLATFORM_SDL
#ifndef LAZY_WINDOW_H
#define LAZY_WINDOW_H

#include <iostream>

namespace Lazy{
    class Window
    {
    protected:
        int width;
        int height;
        void* window;
    public:
        Window(int,int);
        ~Window();
        int HandleEvents();
        int FlipBuffer();
        friend class IGraphicsDevice;
    };
}

#endif
#endif
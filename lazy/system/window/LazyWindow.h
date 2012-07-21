//
//  LazyWindow.h
//  LaZyGame
//
//  Created by Wynter Woods on 7/11/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef __LaZyGame__LazyWindow__
#define __LaZyGame__LazyWindow__

#include <iostream>

namespace Lazy{
    class Window
    {
    protected:
        int width;
        int height;
        void* mainWindow;
        void* renderer;
    public:
        Window(int,int);
        ~Window();
        int HandleEvents();
    };
}

#endif /* defined(__LaZyGame__LazyWindow__) */

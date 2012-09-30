//
//  LazyGraphicsDevice.h
//  LaZyGame
//
//  Created by Wynter Woods on 8/4/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef LAZY_GRAPHICSDEVICE_H
#define LAZY_GRAPHICSDEVICE_H

#include "system/window/LazyWindow.h"
#include <iostream>

namespace Lazy
{
    class GraphicsDevice
    {
    private:
        void* renderer;
        int width;
        int height;
    public:
        static GraphicsDevice* instance;
        
        GraphicsDevice(Window& window);
        ~GraphicsDevice();
        int Clear();
        int Present();
        //void ImageLoad(
    };
}

#endif

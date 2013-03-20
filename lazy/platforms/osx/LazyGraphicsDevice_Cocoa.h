//
//  LazyGraphicsDevice.h
//  LaZyGame
//
//  Created by Wynter Woods on 8/4/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef LAZY_GRAPHICSDEVICE_COCOA_H
#define LAZY_GRAPHICSDEVICE_COCOA_H

#include <lazy/graphics/LazyGraphicsDevice.h>
#include <lazy/system/window/LazyWindow.h>
#include <iostream>
#include <map>

namespace Lazy
{
    class GraphicsDevice_Cocoa : public Lazy::IGraphicsDevice
    {
    public:
        GraphicsDevice_Cocoa(void* window);
        virtual ~GraphicsDevice_Cocoa();
        virtual int Clear();
        virtual int Present();
		virtual int drawString(ResourceHandle fontHandle, std::wstring string, float x, float y);
    };
}

#endif

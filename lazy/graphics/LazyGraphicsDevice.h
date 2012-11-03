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
#include <map>

namespace Lazy
{
    typedef uint32_t RenderTarget;
    typedef uint64_t ResourceHandle;
    
    
    class GraphicsDevice
    {
    public:
        enum ResourceTypes
        {
            ResourceType_Null = 0,
            ResourceType_Image,
            ResourceType_Font,
            ResourceType_VertexBuffer
        };
        struct Resource
        {
            ResourceTypes type;
            void* data;
        };
    private:
        static ResourceHandle resourceIdCounter;
        void* window;
        void* renderer;
        int width;
        int height;
        std::map<ResourceHandle, Resource> resources;
        Lazy::ResourceHandle __createResource();
        void __releaseResource(Resource&);
    public:
        static GraphicsDevice* instance;
        
        GraphicsDevice(Window& window);
        ~GraphicsDevice();
        int Clear();
        int Present();
        //void ImageLoad(
        int loadFont();
        ResourceHandle loadFontFromFile(std::string filename);
        int drawString(std::string string, int x, int y);
    };
}

#endif

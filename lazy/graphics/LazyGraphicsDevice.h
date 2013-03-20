//
//  LazyGraphicsDevice.h
//  LaZyGame
//
//  Created by Wynter Woods on 8/4/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef LAZY_GRAPHICSDEVICE_H
#define LAZY_GRAPHICSDEVICE_H

#include <lazy/system/window/LazyWindow.h>
#include <iostream>
#include <map>

namespace Lazy
{
    typedef uint32_t RenderTarget;
    typedef uint64_t ResourceHandle;
    
    
    class IGraphicsDevice
    {
    public:
        enum ResourceTypes
        {
            ResourceType_Null = 0,
            ResourceType_Image,
            ResourceType_Font,
            ResourceType_VertexBuffer
        };
        struct ResourceData
        {
            ResourceTypes type;
            void* data;
        };
		static ResourceData NilResource;
    protected:
		typedef std::map<ResourceHandle, ResourceData> ResourceMap;
        static ResourceHandle resourceIdCounter;
        void* window;
        void* renderer;
        int width;
        int height;
        ResourceMap resources;
        ResourceHandle __createResource(ResourceTypes type);
        void __releaseResource(ResourceHandle);
		void __setResourceData(ResourceHandle, void* data);
		ResourceData __getResourceData(ResourceHandle);
    public:
        static IGraphicsDevice* instance;
        
        IGraphicsDevice(void* window);
        virtual ~IGraphicsDevice();
        virtual int Clear() = 0;
        virtual int Present() = 0;
        //void ImageLoad(
        virtual int loadFont() = 0;
        ResourceHandle loadFontFromFile(std::string filename);
        virtual int drawString(ResourceHandle fontHandle, std::wstring string, float x, float y);
    };
}

#endif

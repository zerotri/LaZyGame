//
//  LazyGraphicsDevice.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 8/4/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include <lazy/graphics/LazyGraphicsDevice.h>
#include <lazy/system/file/LazyFile.h>
#include <iostream>
#include <vector>


#include "freetype-gl/freetype-gl.h"
#include "freetype-gl/vertex-buffer.h"
#include "freetype-gl/markup.h"

typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
    float r, g, b, a; // color
} vertex_t;

typedef struct {
	texture_atlas_t* atlas;
	texture_font_t* font;
} font_t;




Lazy::IGraphicsDevice::ResourceData Lazy::IGraphicsDevice::NilResource = { Lazy::IGraphicsDevice::ResourceType_Null, NULL};

Lazy::ResourceHandle Lazy::IGraphicsDevice::resourceIdCounter = 0;

Lazy::IGraphicsDevice::IGraphicsDevice(void* window)
{
}
Lazy::IGraphicsDevice::~IGraphicsDevice()
{
}
Lazy::ResourceHandle Lazy::IGraphicsDevice::__createResource(ResourceTypes type)
{
	ResourceData newResource;
	newResource.type = type;
	newResource.data = 0;
	resources[resourceIdCounter] = newResource;
    return resourceIdCounter++;
}
void Lazy::IGraphicsDevice::__releaseResource(ResourceHandle resource)
{
	ResourceMap::iterator resourceIterator = resources.find(resource);
	if(resourceIterator != resources.end())
	{
		ResourceData resource = resourceIterator->second;
		switch (resource.type)
		{
			case ResourceType_Font:
				{
					font_t* fontResource = (font_t*)resource.data;
					texture_atlas_delete( fontResource->atlas );
					texture_font_delete( fontResource->font );
					resources.erase(resourceIterator);
				}
				break;
			case ResourceType_Image:
				{
				}
				break;
			case ResourceType_VertexBuffer:
				{
				}
				break;
			default:
				{
				}
				break;
		}
	}
}
void Lazy::IGraphicsDevice::__setResourceData(ResourceHandle resource, void* data)
{
	ResourceMap::iterator resourceIterator = resources.find(resource);
	if(resourceIterator != resources.end())
	{
		ResourceData& resourceData = resourceIterator->second;
		resourceData.data = data;
	}
}
Lazy::IGraphicsDevice::ResourceData Lazy::IGraphicsDevice:: __getResourceData(Lazy::ResourceHandle resource)
{
	ResourceMap::iterator resourceIterator = resources.find(resource);
	if(resourceIterator != resources.end())
	{
		ResourceData& resourceData = resourceIterator->second;
		return resourceData;
	}
	return NilResource;
}
Lazy::ResourceHandle Lazy::IGraphicsDevice::loadFontFromFile(std::string filename)
{
	std::string resourceFilePath = Lazy::File::getResourcePathForFile(filename.c_str());

	Lazy::ResourceHandle fontHandle = __createResource(ResourceType_Font);
	
	std::cout << "Creating font with handle [" << fontHandle << "] from file: " << resourceFilePath << std::endl;
	
	font_t* font = new font_t;
	font->atlas = texture_atlas_new( 512, 512, 1 );
	font->font = texture_font_new( font->atlas, resourceFilePath.c_str(), 16 );
    texture_font_load_glyphs( font->font, L" !\"#$%&'()*+,-./0123456789:;<=>?"
                             L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                             L"`abcdefghijklmnopqrstuvwxyz{|}~");
	__setResourceData(fontHandle, font);
    return fontHandle;
}
int Lazy::IGraphicsDevice::drawString(ResourceHandle fontHandle, std::wstring string, float x, float y)
{
    return 0;
}

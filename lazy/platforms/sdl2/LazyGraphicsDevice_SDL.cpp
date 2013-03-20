//
//  LazyGraphicsDevice.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 8/4/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//
#include <lazy/LazyConfig.h>
#ifdef PLATFORM_SDL
#include <lazy/graphics/LazyGraphicsDevice.h>
#include <lazy/system/file/LazyFile.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_OpenGL.h"
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


#if defined(__APPLE__)
#  ifdef GL_ES_VERSION_2_0
#    include <OpenGLES/ES2/gl.h>
#  else
#    include <OpenGL/gl.h>
#    include <Glut/glut.h>
#  endif
#elif defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLUT/glut.h> // changed according to your path of glut.h
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif




std::string get_locale_string(const std::wstring & s)
{
	const wchar_t * cs = s.c_str();
	const size_t wn = wcsrtombs(NULL, &cs, 0, NULL);
	
	if (wn == size_t(-1))
	{
		std::cout << "Error in wcsrtombs(): " << errno << std::endl;
		return "";
	}
	
	std::vector<char> buf(wn + 1);
	const size_t wn_again = wcsrtombs(&buf[0], &cs, wn + 1, NULL);
	
	if (wn_again == size_t(-1))
	{
		std::cout << "Error in wcsrtombs(): " << errno << std::endl;
		return "";
	}
	
	assert(cs == NULL); // successful conversion
	
	return std::string(&buf[0], wn);
}

std::wstring get_wstring(const std::string & s)
{
	const char * cs = s.c_str();
	const size_t wn = mbsrtowcs(NULL, &cs, 0, NULL);
	
	if (wn == size_t(-1))
	{
		std::cout << "Error in mbsrtowcs(): " << errno << std::endl;
		return L"";
	}
	
	std::vector<wchar_t> buf(wn + 1);
	const size_t wn_again = mbsrtowcs(&buf[0], &cs, wn + 1, NULL);
	
	if (wn_again == size_t(-1))
	{
		std::cout << "Error in mbsrtowcs(): " << errno << std::endl;
		return L"";
	}
	
	assert(cs == NULL); // successful conversion
	
	return std::wstring(&buf[0], wn);
}




SDL_GLContext mainGLContext = 0;
// --------------------------------------------------------------- add_text ---
void add_text( vertex_buffer_t * buffer, texture_font_t * font, const wchar_t * text, vec4 * color, vec2 * pen );
Lazy::GraphicsDevice::ResourceData Lazy::GraphicsDevice::NilResource = { Lazy::GraphicsDevice::ResourceType_Null, NULL};

Lazy::ResourceHandle Lazy::GraphicsDevice::resourceIdCounter = 0;
Lazy::ResourceHandle Lazy::GraphicsDevice::__createResource(ResourceTypes type)
{
	ResourceData newResource;
	newResource.type = type;
	newResource.data = 0;
	resources[resourceIdCounter] = newResource;
    return resourceIdCounter++;
}
void Lazy::GraphicsDevice::__releaseResource(ResourceHandle resource)
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
void Lazy::GraphicsDevice::__setResourceData(ResourceHandle resource, void* data)
{
	ResourceMap::iterator resourceIterator = resources.find(resource);
	if(resourceIterator != resources.end())
	{
		ResourceData& resourceData = resourceIterator->second;
		resourceData.data = data;
	}
}
Lazy::GraphicsDevice::ResourceData Lazy::GraphicsDevice:: __getResourceData(Lazy::ResourceHandle resource)
{
	ResourceMap::iterator resourceIterator = resources.find(resource);
	if(resourceIterator != resources.end())
	{
		ResourceData& resourceData = resourceIterator->second;
		return resourceData;
	}
	return NilResource;
}

Lazy::GraphicsDevice::GraphicsDevice(Window& window)
: renderer(NULL), width(window.width), height(window.height)
{
    this->renderer = SDL_CreateRenderer((SDL_Window*)window.window, -1, SDL_RENDERER_ACCELERATED);
    if( this->renderer == NULL)
    {
        //throw error here
        std::cout << "Could not init renderer" << std::endl;
    }
    std::cout << "renderer initialized" << std::endl;
    SDL_SetRenderDrawColor((SDL_Renderer*)this->renderer,0,0,0,255);
    
    
    this->window = (SDL_Window*)window.window;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	mainGLContext = SDL_GL_CreateContext((SDL_Window*)window.window);
    if(mainGLContext == NULL)
	{
		printf( "Error creating context!" );
	}
    int32_t status = SDL_GL_MakeCurrent((SDL_Window*)window.window, mainGLContext);
    if (status < 0)
	{
		printf( "Can't set current OpenGL context: %s", SDL_GetError() );
	}
    
    int32_t vPort[4];

	
	//Prepare OpenGL for 2D drawing
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
    
	glGetIntegerv(GL_VIEWPORT, vPort);
    
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    
    glViewport(0, 0, width, height);
	//glOrtho(0, vPort[2], vPort[3], 0, -1, 1);
    glOrtho(0, vPort[2], vPort[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glClearColor(0.25, 0.25, 0.25, 1.0);
    
}
Lazy::GraphicsDevice::~GraphicsDevice()
{
    if( this->renderer != NULL)
    {
        SDL_DestroyRenderer((SDL_Renderer*)this->renderer);
    }
}
int Lazy::GraphicsDevice::Clear()
{
    
	glClearColor(0.25, 0.25, 0.25, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //SDL_RenderClear((SDL_Renderer*)this->renderer);
    return 0;
}
int Lazy::GraphicsDevice::Present()
{
    //SDL_GL_SwapWindow((SDL_Window*)this->window);
    //SDL_RenderPresent((SDL_Renderer*)this->renderer);
    return 0;
}



int Lazy::GraphicsDevice::loadFont()
{
    return 0;
}
Lazy::ResourceHandle Lazy::GraphicsDevice::loadFontFromFile(std::string filename)
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
int Lazy::GraphicsDevice::drawString(ResourceHandle fontHandle, std::wstring string, float x, float y)
{
	ResourceData fontResource = __getResourceData(fontHandle);
	if( fontResource.type == Lazy::GraphicsDevice::ResourceType_Null )
	{
		//error
		return 0;
	}
	font_t* font = (font_t*)fontResource.data;
    vertex_buffer_t *buffer= vertex_buffer_new( "v3f:t2f:c4f" );
    
    vec2 pen = {x,y};
    vec4 black = {255,255,255,1};
    //wchar_t *text = L"A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
	
    add_text( buffer, font->font, string.c_str(), &black, &pen );
    
    glEnable( GL_BLEND );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_COLOR_MATERIAL );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    vertex_buffer_render( buffer, GL_TRIANGLES, "vtc" );
    return 0;
}

void add_text( vertex_buffer_t * buffer, texture_font_t * font,
              const wchar_t * text, vec4 * color, vec2 * pen )
{
    size_t i;
    float r = color->red, g = color->green, b = color->blue, a = color->alpha;
    for( i=0; i < wcslen(text); ++i )
    {
        texture_glyph_t *glyph = texture_font_get_glyph( font, text[i] );
        if( glyph != NULL )
        {
            int kerning = 0;
            if( i > 0)
            {
                kerning = texture_glyph_get_kerning( glyph, text[i-1] );
            }
            pen->x += kerning;
            float x0  = (float)( pen->x + glyph->offset_x );
            float y0  = (float)( pen->y - glyph->offset_y );
            float x1  = (float)( x0 + glyph->width );
            float y1  = (float)( y0 + glyph->height );
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;
            GLuint index = (GLuint)buffer->vertices->size;
            GLuint indices[] = {index, index+1, index+2,
                index, index+2, index+3};
            vertex_t vertices[] = { { x0,y0,0,  s0,t0,  r,g,b,a },
                { x0,y1,0,  s0,t1,  r,g,b,a },
                { x1,y1,0,  s1,t1,  r,g,b,a },
                { x1,y0,0,  s1,t0,  r,g,b,a } };
            vertex_buffer_push_back_indices( buffer, indices, 6 );
            vertex_buffer_push_back_vertices( buffer, vertices, 4 );
            pen->x += glyph->advance_x;
        }
    }
}
#endif
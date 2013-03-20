//
//  LazyGraphicsDevice.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 8/4/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include <lazy/platforms/osx/LazyGraphicsDevice_Cocoa.h>
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


// --------------------------------------------------------------- add_text ---
void add_text( vertex_buffer_t * buffer, texture_font_t * font, const wchar_t * text, vec4 * color, vec2 * pen );


Lazy::GraphicsDevice_Cocoa::GraphicsDevice_Cocoa(void* window)
: IGraphicsDevice(window)
{
    int32_t vPort[4];

	//Prepare OpenGL for 2D drawing
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
    
	glGetIntegerv(GL_VIEWPORT, vPort);
    
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    
    glViewport(0, 0, vPort[2], vPort[3]);
	//glOrtho(0, vPort[2], vPort[3], 0, -1, 1);
    glOrtho(0, vPort[2], vPort[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glClearColor(0.25, 0.25, 0.25, 1.0);
    
}
Lazy::GraphicsDevice_Cocoa::~GraphicsDevice_Cocoa()
{
}
int Lazy::GraphicsDevice_Cocoa::Clear()
{
    
	glClearColor(0.25, 0.25, 0.25, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return 0;
}
int Lazy::GraphicsDevice_Cocoa::Present()
{
    // Let the OpenGLView take care of flushing the buffer
    return 0;
}

int Lazy::GraphicsDevice_Cocoa::drawString(ResourceHandle fontHandle, std::wstring string, float x, float y)
{
	ResourceData fontResource = __getResourceData(fontHandle);
	if( fontResource.type == Lazy::IGraphicsDevice::ResourceType_Null )
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
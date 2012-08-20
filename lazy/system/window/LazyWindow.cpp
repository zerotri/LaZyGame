//
//  LazyWindow.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 7/11/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "LazyWindow.h"
#include "SDL2/SDL.h"

Lazy::Window::Window(int width, int height)
    :   window(NULL),
        width(width),
        height(height)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    window = SDL_CreateWindow("LaZyGame", 0, 0, width, height, 0);
    if( window == NULL)
    {
        //throw error here
    }
}
Lazy::Window::~Window()
{
    if( this->window != NULL)
    {
        SDL_DestroyWindow((SDL_Window*)this->window);
    }
    SDL_Quit();
}

int Lazy::Window::HandleEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    return false;
                break;
        }
    }
    return true;
}
int Lazy::Window::FlipBuffer()
{
    SDL_UpdateWindowSurface((SDL_Window*)this->window);
    return 0;
}
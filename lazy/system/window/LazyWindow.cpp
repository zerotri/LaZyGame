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
    :   mainWindow(NULL),
        renderer(NULL),
        width(width),
        height(height)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    mainWindow = SDL_CreateWindow("LaZyGame", 0, 0, width, height, 0);
    if( mainWindow == NULL)
    {
        //throw error here
    }
    
    renderer = SDL_CreateRenderer((SDL_Window*)mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if( renderer == NULL)
    {
        //throw error here
    }
}
Lazy::Window::~Window()
{
    if( this->renderer != NULL)
    {
        SDL_DestroyRenderer((SDL_Renderer*)this->renderer);
    }
    if( this->mainWindow != NULL)
    {
        SDL_DestroyWindow((SDL_Window*)this->mainWindow);
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
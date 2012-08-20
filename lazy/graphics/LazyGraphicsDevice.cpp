//
//  LazyGraphicsDevice.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 8/4/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "LazyGraphicsDevice.h"
#include "SDL2/SDL.h"
#include <iostream>

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
    SDL_RenderClear((SDL_Renderer*)this->renderer);
    return 0;
}
int Lazy::GraphicsDevice::Present()
{
    SDL_RenderPresent((SDL_Renderer*)this->renderer);
    return 0;
}
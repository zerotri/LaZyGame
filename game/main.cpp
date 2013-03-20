//
//  main.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 7/8/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "main.h"
#include <lazy/graphics/LazyGraphicsDevice.h>
#include <lazy/system/window/LazyWindow.h>
#include <lazy/system/event/LazyEventDistributor.h>
#include <lazy/system/file/LazyFile.h>
#include <Crystal/TypeInfo.h>
#include <iostream>
#include <clocale>

#include <lazy/lua/LazyLua.h>
#include <love/runtime.h>
#include <lunar.h>


const char *program =
"for n,v in pairs(lazy) do\n"
"  print (n,v)\n"
"end\n"
"\n"
"entity = lazy.entity.newEntity(32,0)\n"
"print(lazy.entity.getX(entity))\n"
"print(lazy.entity.getY(entity))\n"
"\n";

// --------------------------------------------------------------- add_text ---




class A : public Lazy::Event
{
public:
    A(Crystal::Id typeId)
    : Lazy::Event(typeId)
    {
    }
};
class B : public Lazy::Event
{
public:
    B(Crystal::Id typeId)
    : Lazy::Event(typeId)
    {
    }
};

int luax_openfile(const char* filename)
{
    //
    return 0;
}

#ifdef __SDL_MAIN__
//main program loop
int main(int argc, char** argv)
{
	std::setlocale(LC_CTYPE, "en_US.utf8");
    lua_State *L = 0;
    
    bool keepRunning = true;
    Lazy::EventDistributor distro;
    //Lazy::Window window(640,480);
    Lazy::GraphicsDevice graphics(window);
    Lazy::Lua::Machine vm;
	Lazy::ResourceHandle font = graphics.loadFontFromFile("Arial Unicode.ttf");
    L = vm.FiberNew();
    vm.LoadProgram(L, program);

    /*distro.subscribe(Crystal::GetTypeId<A>(),
                     [=](const Lazy::Event&)
                     {
                         std::cout << "Received event A" << std::endl;
                     });
    
    distro.input(Crystal::NewObject<A>());
    distro.input(Crystal::NewObject<B>());
    distro.input(Crystal::NewObject<A>());*/
    
    /*if(window == NULL)
    {
        printf("Could not start LazyGame Engine.");
        delete window;
        return 1;
    }*/


    while(keepRunning)
    {
        //vm.Run();
        keepRunning = window.HandleEvents();

		graphics.drawString(font, L"レナート Hello World ﻟﻴﻨﺎﺭﺕ", 32, 64);
        
        
        window.FlipBuffer();
        graphics.Clear();
    }
    lua_close(L);
    return 0;
}
#endif
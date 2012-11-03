//
//  main.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 7/8/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "main.h"
#include "system/window/LazyWindow.h"
#include "graphics/LazyGraphicsDevice.h"
#include "system/event/LazyEventDistributor.h"
#include "Crystal/TypeInfo.h"
#include "system/file/LazyFile.h"
#include <iostream>

#include "lua/LazyLua.h"
#include "love/runtime.h"
#include "lunar.h"


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

//main program loop
int main(int argc, char** argv)
{
    lua_State *L = 0;
    
    bool keepRunning = true;
    Lazy::EventDistributor distro;
    Lazy::Window window(640,480);
    Lazy::GraphicsDevice graphics(window);
    Lazy::Lua::Machine vm;
    L = vm.newFiber();
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
        vm.Run();
        keepRunning = window.HandleEvents();
        graphics.Present();
        
        
        
        window.FlipBuffer();
        graphics.Clear();
    }
    lua_close(L);
    return 0;
}
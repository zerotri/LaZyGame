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
#include <iostream>

extern "C" {
#include "Lua/src/lua.h"
#include "Lua/src/lauxlib.h"
#include "Lua/src/lualib.h"
}
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

//main program loop
int main(int argc, char** argv)
{
    lua_State *L = luaL_newstate();
    //lua_State *Lt[1000];
    
    bool keepRunning = true;
    Lazy::EventDistributor distro;
    Lazy::Window window(640,480);
    Lazy::GraphicsDevice graphics(window);
    
    //luaL_openlibs(L);
    luaopen_io(L);
    luaopen_base(L);
    //Lazy::Lua::registerTypes(L);
    Lazy::Lua::registerTypes(L);
    
    //Lunar<Account>::Register(L);

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
    
    luaL_loadbuffer(L, program, strlen(program), "code");
    
    int error = lua_pcall(L, 0, 0, 0);
    if (error) {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    
    /*for (int i = 0; i < 1000; i++) {
        Lt[i] = lua_newthread(L);
        lua_getglobal(Lt[i], "main");
    }*/
    
    //lua_getglobal(L, "draw");
    //lua_pcall(L, 0, 0, 0);

    while(keepRunning)
    {
        //for (int i = 0; i < 1000; i++) {
        //    lua_resume(Lt[i], 0, 0);
        //}
        keepRunning = window.HandleEvents();
        graphics.Present();
        window.FlipBuffer();
        graphics.Clear();
    }
    lua_close(L);
    return 0;
}
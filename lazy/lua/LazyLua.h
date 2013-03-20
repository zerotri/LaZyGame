//
//  LazyLua.h
//  LaZyGame
//
//  Created by Wynter Woods on 9/10/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef LAZY_LUA_H
#define LAZY_LUA_H

extern "C" {
#include <lua/src/lua.h>
#include "lua/src/lauxlib.h"
#include "lua/src/lualib.h"
}
#include <stdio.h>
#include <vector>
#include <algorithm>


namespace Lazy
{
    namespace Lua
    {
        namespace System
        {
            int lua_pause(lua_State *L);
        }
        int registerTypes(lua_State* L);
        class Machine
        {
        private:
            lua_State* mainFiber;
            std::vector<lua_State*> fibers;
			std::vector<lua_State*> fibersEnding;
        public:
            static bool RunFiber(lua_State* L)
            {
                int status = 0;
                lua_resume(L, 0, 0);
				if(status != LUA_YIELD)
				{
					if (status == LUA_ERRRUN && lua_isstring(L, -1)) {
						printf("isstring: %s\n", lua_tostring(L, -1));
						lua_pop(L, -1);
					}
					return true;
				}
				return false;
            }
            Machine()
            {
                mainFiber = luaL_newstate();
                
                //luaopen_io(L);
                //luaopen_base(L);
                
                Lazy::Lua::registerTypes(mainFiber);
                lua_register(mainFiber, "yield", System::lua_pause);
                fibers.push_back(mainFiber);
            }
            lua_State* FiberNew()
            {
                lua_State* fiber = lua_newthread(mainFiber);
                lua_getglobal(fiber, "main");
                
                
                fibers.push_back(fiber);
                return fiber;
            }
            int LoadProgram(lua_State* L, const char* program)
            {
                luaL_loadbuffer(L, program, strlen(program), "code");
                
                int error = lua_pcall(L, 0, 0, 0);
                if (error) {
                    fprintf(stderr, "%s", lua_tostring(L, -1));
                    lua_pop(L, 1);
                    return 1;
                }
                return 0;
            }
            int Call(lua_State* L, const char* function)
            {
                lua_getglobal(L, function);
                lua_pcall(L, 0, 0, 0);
                return 0;
            }
            int Run()
            {
				// Run through all fibers, removing those that have yielded
				// or caused an error
				std::remove_if(fibers.begin(), fibers.end(), RunFiber);
                return 0;
            }
        };
        namespace Entity
        {
            extern "C" int luaopen_lazy_entity(lua_State * L);
            int w_newEntity(lua_State* L);
            int w_getX(lua_State * L);
            int w_getY(lua_State * L);
        }
    }
}
#endif

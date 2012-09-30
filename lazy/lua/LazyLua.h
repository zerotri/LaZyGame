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
#include "Lua/src/lua.h"
#include "Lua/src/lauxlib.h"
#include "Lua/src/lualib.h"
}
namespace Lazy
{
    namespace Lua
    {
        int registerTypes(lua_State* L);
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

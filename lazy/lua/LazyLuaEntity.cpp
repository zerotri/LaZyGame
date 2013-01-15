//
//  LazyLuaEntity.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 9/23/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "LazyLua.h"
#include "LazyEntity.h"
#include "love/runtime.h"
#include "love/types.h"


namespace Lazy
{
    namespace Lua
    {
        namespace Entity
        {
            //static class Entity* instance = 0;
            int w_newEntity(lua_State * L)
            {
                printf("Entered newEntity\n");
                //ENTITY_TYPE_ID
                // Case 1: Integers.
                if(lua_isnumber(L, 1))
                {
                    int x = luaL_checkint(L, 1);
                    int y = luaL_checkint(L, 2);
                    Lazy::Entity * t = new Lazy::Entity(x, y);
                    love::luax_newtype(L, "Entity", love::ENTITY_ENTITY_T, (void*)t);
                    return 1;
                }
                return 0;
            };
            int w_getX(lua_State * L)
            {
                if(love::luax_istype(L, 1, love::ENTITY_ENTITY_T))
                {
                    Lazy::Entity * e = love::luax_checktype<Lazy::Entity>(L, 1, "Entity", love::ENTITY_ENTITY_T);
                    lua_pushinteger(L, e->getX());
                    return 1;
                }
                return 0;
            };
            int w_getY(lua_State * L)
            {
                if(love::luax_istype(L, 1, love::ENTITY_ENTITY_T))
                {
                    Lazy::Entity * e = love::luax_checktype<Lazy::Entity>(L, 1, "Entity", love::ENTITY_ENTITY_T);
                    lua_pushinteger(L, e->getY());
                    return 1;
                }
                return 0;
            };

            static const luaL_Reg functions[] = {
                
                // Data
                { "newEntity", w_newEntity },
                
                { "getX", w_getX },
                { "getY", w_getY },
                { 0, 0 }
            };
            extern "C" int luaopen_lazy_entity(lua_State * L)
            {
                luaL_setfuncs(L, functions, 1);
                return 1;
            }
        }
    }
}
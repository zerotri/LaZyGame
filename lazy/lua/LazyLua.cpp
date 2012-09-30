//
//  LazyLua.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 9/27/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "LazyLua.h"
#include "love/runtime.h"

namespace Lazy
{
    namespace Lua
    {
        int registerTypes(lua_State* L)
        {
            static const luaL_Reg modules[] = {
                { "entity", Lazy::Lua::Entity::luaopen_lazy_entity },
                /*{ "love.audio", love::audio::luaopen_love_audio },
                { "love.event", love::event::sdl::luaopen_love_event },
                { "love.filesystem", love::filesystem::physfs::luaopen_love_filesystem },
                { "love.font", love::font::freetype::luaopen_love_font },
                { "love.graphics", love::graphics::opengl::luaopen_love_graphics },
                { "love.image", love::image::luaopen_love_image },
                { "love.joystick", love::joystick::sdl::luaopen_love_joystick },
                { "love.keyboard", love::keyboard::sdl::luaopen_love_keyboard },
                { "love.mouse", love::mouse::sdl::luaopen_love_mouse },
                { "love.physics", love::physics::box2d::luaopen_love_physics },
                { "love.sound", love::sound::luaopen_love_sound },
                { "love.timer", love::timer::sdl::luaopen_love_timer },
                { "love.thread", love::thread::sdl::luaopen_love_thread },*/
                { 0, 0 }
            };
            love::luax_insistglobal(L, "lazy");
            lua_newtable(L);
            lua_pop(L, 1);
            for(int i = 0; modules[i].name != 0; i++)
            {
                love::luax_insist(L, 1, modules[i].name );
                lua_newtable(L);
                modules[i].func(L);
                lua_pop(L, 1);
            }
            //Lazy::Lua::Entity::luaopen_lazy_entity(L);
            //love::luax_preload(L, Lazy::Lua::Entity::luaopen_lazy_entity, "lazy.entity");
            return 1;
        }
    }
}
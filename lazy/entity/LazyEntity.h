//
//  LazyEntity.h
//  LaZyGame
//
//  Created by Wynter Woods on 9/23/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef LAZY_ENTITY_H
#define LAZY_ENTITY_H

#include <iostream>
#include <love/Module.h>

namespace Lazy
{
    class Entity : public love::Module
    {
    public:
        Entity(int x, int y);
        
        uint64_t getX()
        {
            return x;
        }
        uint64_t getY()
        {
            return y;
        }
        /**
         * Gets the name of the module. This is used in case of errors
         * and other messages.
         *
         * @return The full name of the module, eg. love.graphics.opengl.
         **/
		virtual const char * getName() const;
    private:
        uint64_t x;
        uint64_t y;
    };
}

#endif
//
//  LazyEntity.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 9/23/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "LazyEntity.h"

Lazy::Entity::Entity(int x, int y)
:x(x), y(y)
{
    
}

const char * Lazy::Entity::getName() const
{
    return "lazy.entity";
}
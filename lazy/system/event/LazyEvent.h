//
//  LazyEvent.h
//  LaZyGame
//
//  Created by Wynter Woods on 7/11/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef __LaZyGame__LazyEvent__
#define __LaZyGame__LazyEvent__

#include <iostream>
#include "Crystal/Object.h"

namespace Lazy
{
    class Event : public Crystal::Object
    {
    private:
    public:
        Event(Crystal::Id typeId)
        : Crystal::Object(typeId)
        {
        }
    };
}
#endif /* defined(__LaZyGame__LazyEvent__) */

//----------------------------------------------------------------------------
// File:         LazyEvent.h
// Description:  An event system for the Crystal library
//----------------------------------------------------------------------------
#ifndef LAZY_EVENT_H
#define LAZY_EVENT_H

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
#endif

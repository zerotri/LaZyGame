//
//  LazyEventDistributor.h
//  LaZyGame
//
//  Created by Wynter Woods on 7/11/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef __LaZyGame__LazyEventDistributor__
#define __LaZyGame__LazyEventDistributor__

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include "LazyEvent.h"

namespace Lazy
{
    class EventDistributor
    {
    protected:
        typedef std::function<void (const Lazy::Event&)> eventFunctor;
        typedef std::map<Crystal::Id, std::vector< eventFunctor > > subscriptionMap;
        std::vector<Lazy::Event> events;
        subscriptionMap eventSubscriptions;
    public:
        void input(Event*);
        void subscribe(Crystal::Id, std::function<void (const Lazy::Event&) >);
    };
}
#endif /* defined(__LaZyGame__LazyEventDistributor__) */

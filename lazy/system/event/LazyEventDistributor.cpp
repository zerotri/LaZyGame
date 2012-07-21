//
//  LazyEventDistributor.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 7/11/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "LazyEventDistributor.h"

void Lazy::EventDistributor::input(Event* event)
{
    subscriptionMap::iterator subscription = eventSubscriptions.find(event->getTypeId());
    if(subscription != eventSubscriptions.end())
    {
        for(eventFunctor &functor : subscription->second)
        {
            functor(*event);
        }
    }
}

void Lazy::EventDistributor::subscribe(Crystal::Id id, std::function<void (const Lazy::Event&) > functor)
{
    eventSubscriptions[id].push_back(functor);
}
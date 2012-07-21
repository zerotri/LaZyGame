//
//  main.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 7/8/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "main.h"
#include "system/window/LazyWindow.h"
#include "system/event/LazyEventDistributor.h"
#include "Crystal/TypeInfo.h"
#include <iostream>



class A : public Lazy::Event
{
public:
    A(Crystal::Id typeId)
    : Lazy::Event(typeId)
    {
    }
};
class B : public Lazy::Event
{
public:
    B(Crystal::Id typeId)
    : Lazy::Event(typeId)
    {
    }
};

//main program loop
int main(int argc, char** argv)
{
    bool keepRunning = true;
    Lazy::EventDistributor distro;
    Lazy::Window* window = new Lazy::Window(640,480);
    
    distro.subscribe(Crystal::GetTypeId<A>(), [=](const Lazy::Event&)
                        {
                            std::cout << "Received event A" << std::endl;
                        });
    
    distro.input(Crystal::NewObject<A>());
    distro.input(Crystal::NewObject<B>());
    distro.input(Crystal::NewObject<A>());
    
    if(window == NULL)
    {
        printf("Could not start LazyGame Engine.");
        delete window;
        return 1;
    }
    
    while(keepRunning)
    {
        keepRunning = window->HandleEvents();
    }

    delete window;
    return 0;
}
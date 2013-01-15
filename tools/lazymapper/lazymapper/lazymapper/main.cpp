//
//  main.cpp
//  lazymapper
//
//  Created by Wynter Woods on 11/5/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include <Poco/Logger.h>
#include <Poco/Environment.h>
#include <iostream>
#include <functional>
#include <vector>
#include <map>

typedef std::vector<std::string> ArgumentVector;
//typedef std::map<std::string, std::function<void(ArgumentVector)> > CommandMap;

int main(int argc, const char * argv[])
{
	std::cout << Poco::Environment::osName() << std::endl;
	if (Poco::Environment::has("HOME"))
        std::cout << "Home: " << Poco::Environment::get("HOME") << std::endl;
    ArgumentVector arguments;
    CommandMap commands;
    
    // ==== map ==== //
    commands["map"] = [](ArgumentVector arguments)
    {
		//Poco::Logger& logger = Poco::Logger::get("TestLogger");
		if(arguments.size() < 1)
		{
			//logger.information("map command requires at least one argument!");
			std::cout
				<< std::endl
				<< "examples:" << std::endl
				<< std::endl
				<< "map new - creates a new map" << std::endl
				<< "map save [filename] - creates a new map" << std::endl
				<< "map load [filename] - creates a new map" << std::endl;
			return;
		}
    };
    
    // ==== map ==== //
    
    // push program arguments into arguments vector as type string
    for(int arg = 0; arg < argc; arg++)
    {
        arguments.push_back(std::string(argv[arg]));
        std::cout << "Argument " << arg << ": " << arguments[arg] << std::endl;
    }
	
	// verify that the program was called with at least one argument
	if( arguments.size() > 1 )
	{
		// if not, error and exit.
		std::cout << "Please specify command/arguments." << std::endl;
		return 1;
	}

	// determine command based on
	auto command = arguments[0];
	arguments.erase(arguments.begin());
	auto currentCommand = commands.find(command);
	if(currentCommand != commands.end())
	{
		currentCommand->second(arguments);
	}
	else
	{
		std::cout << "Unknown command: " << command << std::endl;
	}
    return 0;
}


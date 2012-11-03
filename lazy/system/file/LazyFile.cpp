//
//  LazyFile.cpp
//  LaZyGame
//
//  Created by Wynter Woods on 10/11/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#include "LazyFile.h"

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

std::string Lazy::File::getResourcePathForFile(std::string filename)
{
#ifdef WINDOWS
    return std::string("Data/") + filename;
#elif defined(LINUX)
    return std::string("Data/") + filename;
#else   // MAC OS X
    
    // ----------------------------------------------------------------------------
    // This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        return std::string("Data/") + filename;
    }
    CFRelease(resourcesURL);
    return std::string(path) + std::string("/") + filename;
#else
    // ----------------------------------------------------------------------------
    return std::string("Data/") + filename;
#endif
#endif
}
//
//  LazyFile.h
//  LaZyGame
//
//  Created by Wynter Woods on 10/11/12.
//  Copyright (c) 2012 Wynter Woods. All rights reserved.
//

#ifndef __LaZyGame__LazyFile__
#define __LaZyGame__LazyFile__

#include <iostream>


namespace Lazy
{
	class File
	{
	public:
        static std::string getResourcePathForFile(std::string filename);
	};
}

#endif /* defined(__LaZyGame__LazyFile__) */

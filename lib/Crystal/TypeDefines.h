//----------------------------------------------------------------------------
// File:         Types.h
// Description:  Basic typedef's for the Crystal library
//----------------------------------------------------------------------------
#ifndef CRYSTAL_TYPES_H
#define CRYSTAL_TYPES_H
#include <string>
#include <stdint.h>
//#include <Poco/String.h>
namespace Crystal {
	template<typename ComponentType>
	struct Color
	{
		Color() {};
		Color(ComponentType r, ComponentType g, ComponentType b, ComponentType a)
			:r(r), g(g), b(b), a(a) {};
		Color(Color const & other)
			:r(other.r), g(other.g), b(other.b), a(other.a) {};
		ComponentType r;
		ComponentType g;
		ComponentType b;
		ComponentType a;
	};
	struct Second
	{
		double value;
	};
	struct Millisecond
	{
		double value;
	};
	//constexpr Value

	//#define nil NULL
	//#define self (*this)
	//#define abstract =0
    typedef uint64_t    Id;
	typedef double Time;
	typedef double FloatingPoint;
	
	// Strings
	typedef std::string String;
	/*std::string operator "" _str(const char* str, size_t)
	{
		return std::string(str);
	}*/
}
#endif

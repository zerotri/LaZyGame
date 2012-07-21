//----------------------------------------------------------------------------
// File:         Types.h
// Description:  Basic typedef's for the Crystal library
//----------------------------------------------------------------------------
#ifndef CRYSTAL_MATH_H
#define CRYSTAL_MATH_H
#include <iostream>
namespace Crystal
{
	template<typename T>
	T Absolute(T value)
	{
		return (value >= 0) ? value : -value;
	}

	template<typename T>
	T Max(T one, T two)
	{
		return one > two ? one : two;
	}

	template<typename T>
	T Min(T one, T two)
	{
		return one < two ? one : two;
	}

	template<typename T>
	T Difference(T one, T two)
	{
		return Absolute(one - two);
	}

	template<typename T>
	T Lerp(T one, T two, Crystal::FloatingPoint amount)
	{
		return T(one + ((T)(two - one) * amount));
	}

	template<typename T>
	T Clamp(T value, T min, T max)
	{
		return Max(min, Min(max, value));
	}

	template<typename T>
	T SmoothStep(T one, T two, Crystal::FloatingPoint amount)
	{
		Crystal::FloatingPoint num = Crystal::Clamp<Crystal::FloatingPoint>(amount, 0.0, 1.0);
		return Lerp(one, two, (num*num) * (3.0 - (2.0 * num)));
	}
}
#endif
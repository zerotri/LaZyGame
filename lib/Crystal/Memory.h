//----------------------------------------------------------------------------
// File:         Memory.h
// Description:  Memory utilities for the Crystal library
//----------------------------------------------------------------------------

#ifndef CRYSTAL_MEMORY_H
#define CRYSTAL_MEMORY_H
//#include <memory>
#include <Crystal/TypeDefines.h>
namespace Crystal {
	//----------------------------------------------------------------------------
	// Method: MemoryAllocate
	//----------------------------------------------------------------------------
	template <typename _T>
	_T* MemoryAllocate(uint32_t size = 1)
	{
	    return new _T[size];
	}

	//----------------------------------------------------------------------------
	// Method: MemoryAllocate
	//----------------------------------------------------------------------------
	template <typename _T>
	void CopyBlock(_T* src, _T* dst, const uint32_t blockSize)
	{
	    memcpy(dst, src, blockSize);
	}
	template <typename _T>
	_T* CopyRegion2D(_T* src, const uint32_t width, const uint32_t height, const uint32_t stride)
	{
	    _T* newPtr = new _T[width*height];
	    uint8_t* srcPtr = (uint8_t*)src;
	    uint8_t* dstPtr = (uint8_t*)newPtr;
	    for(uint32_t i = 0; i < height; i++, srcPtr += stride*sizeof(_T), dstPtr += width*sizeof(_T))
	    {
	        CopyBlock<uint8_t>(srcPtr, dstPtr, width*sizeof(_T));
	    }
	    return newPtr;
	}
	//----------------------------------------------------------------------------
	// Method: MemoryZero
	//		Provides a fast an easy way to zero a region of memory, such as an
	//		array or struct. Should NOT be used on C++ classes if the class
	//		requires a constructor to initialize it. Another function has been
	//		created to allow zero & reinitialization of object memory.
	//
	// NOTE: Should not be used on STL classes. Most of these have intricate
	//		methods of allocation and construction, or rather, they will give an
	//		exception due to accessing an uninitialized pointer.
	//----------------------------------------------------------------------------
	template <typename _T>
	void FillBlock(_T* destination, int32_t value, const uint32_t blockSize)
	{
	    memset(destination, value, blockSize);
	}
	/*template <typename _T>
	_T* FillRegion2D(_T* src, const uint32_t width, const uint32_t height, const uint32_t stride)
	{
	    _T* newPtr = new _T[width*height];
	    uint8_t* srcPtr = (uint8_t*)src;
	    uint8_t* dstPtr = (uint8_t*)newPtr;
	    for(int32_t i = 0; i < height; i++, srcPtr += stride*sizeof(_T), dstPtr += width*sizeof(_T))
	    {
	        FillBlock<uint8_t>(srcPtr, dstPtr, width*sizeof(_T));
	    }
	    return newPtr;
	}*/
	//----------------------------------------------------------------------------
	// Method: MemoryZero
	//		Provides a fast an easy way to zero a region of memory, such as an
	//		array or struct. Should NOT be used on C++ classes if the class
	//		requires a constructor to initialize it. Another function has been
	//		created to allow zero & reinitialization of object memory.
	//
	// NOTE: Should not be used on STL classes. Most of these have intricate
	//		methods of allocation and construction, or rather, they will give an
	//		exception due to accessing an uninitialized pointer.
	//----------------------------------------------------------------------------
	template <typename _T>
	void ZeroMemory(_T& object)
	{
		memset(&object, 0, sizeof(_T));
	}

	//----------------------------------------------------------------------------
	// Method: ClassZero
	//		Provides a fast an easy way to make a copy of memory. It can be used
	//		like either of the following examples:
	//		u8_t* somePointer = Crystal::CopyMemory<u8_t>(oldPointer, 32);
	//
	//		Vertex* newVertex = Crystal::CopyMemory<Vertex>(oldVertex);
	//
	//		Where in the first example a size is specified, in the second it is
	//		taken as the size of the type provided because no size was specified
	//----------------------------------------------------------------------------
	template <typename _T>
	_T* CopyMemory(_T* ptr, uint32_t size = 0)
	{
	    _T* newPtr = 0;
	    if(size == 0)
	    {
	        newPtr = new uint8_t[sizeof(_T)];
	        memcpy(newPtr, ptr, sizeof(_T));
	    }
	    else
	    {
	        newPtr = new uint8_t[size];
	        memcpy(newPtr, ptr, size);
	    }
	    return newPtr;
	}
	//----------------------------------------------------------------------------
	// Method: ClassZero
	//		Provides a fast an easy way to zero an object. Useful only if the
	//		object being zero'ed contains a public constructor, otherwise this is
	//		rather useless.
	//----------------------------------------------------------------------------
	template <typename _object>
	void ZeroInstance(_object& instance)
	{
		instance._object::~_object();
		memset(&instance, 0, sizeof(_object));
		instance._object::_object();
	}

}
//void* operator new (size_t size);
//void operator delete (void *p);
#endif
//----------------------------------------------------------------------------
// File:         Object.h
// Description:  Base object class for the Crystal library
//----------------------------------------------------------------------------
#ifndef CRYSTAL_OBJECT_H
#define CRYSTAL_OBJECT_H
#include <Crystal/TypeDefines.h>
#include <Crystal/TypeInfo.h>
namespace Crystal {
	class IObject
	{
	public:
	private:
	};

	// ----------------------------------------------
	// Class: Object
	// Defines a base class for all Crystal objects
	// to derive from, providing a consistent set of
	// utilities to aid in development.
	//
	// Todo:
	// A correct implementation of Object will have
	// garbage collection, smart pointer access
	// ----------------------------------------------
    
    template<typename PropertyType>
    static PropertyType* NewObject()
    {
        return new PropertyType(Crystal::GetTypeId<PropertyType>());
    }
	class Object
	{
#ifdef CRYSTAL_USE_OLD_TYPEINFO
	HasTypeInfo;
#endif
	public:
		// ----------------------------------------------
		// ctor()
		// ----------------------------------------------
		Object(Crystal::Id typeId)
        : typeId(typeId)
		{
		}

		// ----------------------------------------------
		// dtor()
		// ----------------------------------------------
		virtual ~Object()
		{
		}
        /*template<typename PropertyType>
        static uint64_t getTypeId()
        {
            static uint64_t typeId(TypeInfo_GetNextType());
            return typeId;
        }*/
        
        Crystal::Id getTypeId()
        {
            return typeId;
        }
    protected:
        Crystal::Id id;
        Crystal::Id typeId;
        
        static Crystal::Id GetNextId()
        {
            static Crystal::Id next_id(0);
            return next_id++;
        }
	};
}
#endif

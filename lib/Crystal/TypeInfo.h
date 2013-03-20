//----------------------------------------------------------------------------
// File:         TypeInfo.h
// Description:  RTTI class and utilities for the Crystal library
//----------------------------------------------------------------------------
#ifndef CRYSTAL_TYPEINFO_H
#define CRYSTAL_TYPEINFO_H

#include <cstdarg>
#include <string>
#include <Crystal/TypeDefines.h>

#ifdef CRYSTAL_OUTPUT_VERBOSE_DEBUG_INFO
    #include <iostream>
#endif

namespace Crystal {
#ifndef CRYSTAL_USE_OLD_TYPEINFO
    // ----------------------------------------------
	// class: TypeInfo (Version 2)
	// A custom Run Time Type Identification class.
	// By adding a few macros into your class, you
	// can give it TypeInfo properties.
	// To use, create a new class, based on imaginary
	// classes 'A' and 'C':
	// 
	//  class BaseClass : public A, public C{
	//  };
	// 
	// Then, in that classes' implementation file,
	// place the following macro:
	// 
	//  associateBaseTypes(BaseClass,0);
	// 
	// But WAIT! TypeInfo doesn't know anything about
	// BaseClass' parents!
	// 
	// NOTE: if the class being given TypeInfo
	// properties derives from any classes, you must
	// add class info to the end of the
	// TYPEINFO_IMPLEMENTATION macro as follows:
	// 
	//  associateBaseTypes(BaseClass, 2, CLASS(A), CLASS(C));
	// 
	// And now you have a fully functioning class
	// with TypeInfo properties. To check the classes
	// type, you can now do the following:
	// 
	//  if(a_class->RTTI().isOfType(CLASS(BaseClass)))
	//  {
	//      //Do something since we know 'a_class' IS a BaseClass
	//  }
	//
	// ----------------------------------------------
    
    // ----------------------------------------------
    // ITypeInfo
    // ----------------------------------------------
    class ITypeInfo
    {
    protected:
        Crystal::Id id;
        //ITypeInfo* parent;
        //std::vector<ITypeInfo*> children;
    public:
        Crystal::Id getId()
        {
            return this->id;
        }
        static uint64_t GetNextTypeId()
        {
            static uint64_t next_id(0);
            return next_id++;
        }
    };

    // ----------------------------------------------
    // TypeInfo
    // ----------------------------------------------
    template<typename PropertyType>
    class TypeInfo : public ITypeInfo
    {
    public:
        // ----------------------------------------------
		// ctor()
		// 
		// ----------------------------------------------
        TypeInfo(Crystal::Id id)
        {
            this->id = id;
#ifdef CRYSTAL_OUTPUT_VERBOSE_DEBUG_INFO
            std::cout << "New Type ID: "<< this->id << std::endl;
#endif
        }
    };
    template<typename PropertyType>
    static ITypeInfo& GetTypeInfo()
    {
        static TypeInfo<PropertyType> typeInfo(ITypeInfo::GetNextTypeId());
        return typeInfo;
    }
    template<typename PropertyType>
    static Crystal::Id GetTypeId()
    {
        return Crystal::GetTypeInfo<PropertyType>().getId();
    }
#else
	// ----------------------------------------------
	// class: TypeInfo
	// A custom Run Time Type Identification class.
	// By adding a few macros into your class, you
	// can give it TypeInfo properties.
	// To use, create a new class, based on imaginary
	// classes 'A' and 'C':
	// 
	//  class BaseClass : public A, public C{
	//      hasTypeInfo;
	//  };
	// 
	// Then, in that classes' implementation file,
	// place the following macro:
	// 
	//  associateBaseTypes(BaseClass,0);
	// 
	// But WAIT! TypeInfo doesn't know anything about
	// BaseClass' parents!
	// 
	// NOTE: if the class being given TypeInfo
	// properties derives from any classes, you must
	// add class info to the end of the
	// TYPEINFO_IMPLEMENTATION macro as follows:
	// 
	//  associateBaseTypes(BaseClass, 2, CLASS(A), CLASS(C));
	// 
	// And now you have a fully functioning class
	// with TypeInfo properties. To check the classes
	// type, you can now do the following:
	// 
	//  if(a_class->RTTI().isOfType(CLASS(BaseClass)))
	//  {
	//      //Do something since we know 'a_class' IS a BaseClass
	//  }
	//
	// ----------------------------------------------
	class TypeInfo
	{
	public:
		// ----------------------------------------------
		// ctor()
		// set up the class RTTI info, including the name
		// and parents' names
		// ----------------------------------------------
		TypeInfo(const Crystal::String& name, int32_t parentCount, ...)
		:	className(name)
		{
			//Check if this class has any parents.
			if(parentCount < 1)
			{
				//If not, not much needs to be done
				this->parentCount = 0;
				this->parentClasses = 0;
			}
			else
			{
				//If it does though, load the parent info into this RTTI class
				this->parentCount = parentCount;
				this->parentClasses = new const TypeInfo*[parentCount];

				//Since we're using a variable arguments contructor, we get to
				//have fun with va_lists
				va_list v;
				va_start(v, parentCount);

				//Iterate over va_list
				for(int32_t currentParent = 0; currentParent < parentCount; ++currentParent)
				{
					//Loading parent info into 'parentClasses' array
					this->parentClasses[currentParent] = va_arg(v, const TypeInfo*);
				}
			}
		};

		// ----------------------------------------------
		// getClassName()
		// Return the name of the class
		// ----------------------------------------------
		const Crystal::String& GetClassName() const
		{
			return this->className;
		};

		// ----------------------------------------------
		// isOfType()
		// Return if the class is a class of type
		// [a_cOtherRTTI], or if it even derives from it
		// ----------------------------------------------
		bool IsOfType(const TypeInfo& otherType) const
		{
			const TypeInfo& pCompare = (*this);

			if(&pCompare == &otherType)
				return true;

			//If not, let's check this class' parents
			for(int32_t currentParent = 0; currentParent < this->parentCount; ++currentParent)
			{
				//And while we're at it, all the ancestors will be taken into account as well
				if(this->parentClasses[currentParent]->IsOfType(otherType))
					return true;
			}
			//Oops!
			//These classes are NOT the same, or even related
			return false;
		}

		// ----------------------------------------------
		// operator < ()
		// Performs a check to see if this type is a
		// descendant of the other type being compared
		// ----------------------------------------------
		bool operator < (const TypeInfo& otherType) const
		{
			return IsOfType(otherType);
		}

		// ----------------------------------------------
		// operator == ()
		// Performs a check to see if this type is the
		// same as the other type being compared. This
		// does not test against parent types.
		// ----------------------------------------------
		bool operator == (const TypeInfo& otherType) const
		{
			return (this == &otherType);
		}
	private:
		const Crystal::String className;
		int32_t parentCount;
		const TypeInfo** parentClasses;
	};

	#define HasTypeInfo \
	public: \
	static const Crystal::TypeInfo typeInfo; \
	virtual const Crystal::TypeInfo* GetType() const { return &this->typeInfo; };
	
	#define AssociateBaseTypes(name, ...) \
	const Crystal::TypeInfo name::typeInfo(Crystal::String(#name), __VA_ARGS__);
	
	#define CLASS(class) (&class::typeInfo)
	#define PCLASS(class) (&class->typeInfo)
	#define RCLASS(class) (&class.typeInfo)

	#define runType(object) (object->typeInfo)
#endif
}
#endif


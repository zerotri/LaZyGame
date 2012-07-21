//----------------------------------------------------------------------------
// File:         Event.h
// Description:  An event system for the Crystal library
//----------------------------------------------------------------------------
#ifndef CRYSTAL_EVENT_H
#define CRYSTAL_EVENT_H

#include <map>
#include <Crystal/Object.h>
#include <Crystal/TypeInfo.h>
#include <EfficientDelegates/include/sigslot.h>
#include <unordered_map>
#include <iostream>

#ifdef CRYSTAL_USE_OLD_EVENTS
namespace Crystal {
	// ----------------------------------------------
	// class: Event
	// provides a basic interface to base Events on.
	// ----------------------------------------------
	class Event : public Crystal::Object
	{
#ifdef CRYSTAL_USE_OLD_TYPEINFO
	HasTypeInfo;
#endif
	protected:
		// ----------------------------------------------
		// ctor()
		// set up Event class interface and init
		// Crystal::Object base class.
		// ----------------------------------------------
		Event() : Crystal::Object() {}

		// ----------------------------------------------
		// dtor()
		// ----------------------------------------------
		virtual ~Event() {};
	};

	class IFunctionHandler
	{
	public:
		virtual ~IFunctionHandler() {};
		void Execute(const Event& event)
		{
			this->Call(event);
		}

	private:
		virtual void Call(const Event&) = 0;
	};


	template <class T, class EventT>
	class MemberFunctionHandler : public IFunctionHandler
	{
	public:
		typedef void (T::*MemberFunc)(EventT&);
		MemberFunctionHandler(T* instance, MemberFunc memFn) : _instance(instance), _function(memFn) {};

		void Call(const Event& event)
		{
			(_instance->*_function)(*static_cast<EventT*>(&event));
		}

	private:
		T* _instance;
		MemberFunc _function;
	};


	class EventHandler : public Crystal::Object
	{
#ifdef CRYSTAL_USE_OLD_TYPEINFO
	HasTypeInfo;
#endif
	public:
		EventHandler() : Crystal::Object() {}
		~EventHandler()
		{
			Handlers::iterator it = _handlers.begin();
			while(it != _handlers.end())
			{
				delete it->second;
				++it;
			}
			_handlers.clear();
		}
		void ExecuteEvent(const Event& event)
		{
#ifdef CRYSTAL_USE_OLD_TYPEINFO
			Handlers::iterator it = _handlers.find(event.GetType());
			if(it != _handlers.end())
			{
				it->second->Execute(event);
			}
#endif
		}

		template <class T, class EventT>
		void RegisterEventFunc(T*, void (T::*memFn)(EventT&));

	private:
#ifdef CRYSTAL_USE_OLD_TYPEINFO
		typedef std::map<const Crystal::TypeInfo*, IFunctionHandler*> Handlers;
#else
        typedef std::map<const Crystal::ITypeInfo*, IFunctionHandler*> Handlers;
#endif
		Handlers _handlers;
	};


	template <class T, class EventT>
	void EventHandler::RegisterEventFunc(T* obj, void (T::*memFn)(EventT&))
	{
#ifdef CRYSTAL_USE_OLD_TYPEINFO
		_handlers[CLASS(EventT)]= new MemberFunctionHandler<T, EventT>(obj, memFn);
#endif
	}
}
#endif
#endif
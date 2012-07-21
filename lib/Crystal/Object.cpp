//----------------------------------------------------------------------------
// File:         Object.cpp
// Description:  Base object implementations (RTTI definitions so far)
//----------------------------------------------------------------------------
#include <Crystal/Object.h>
#include <Crystal/Event.h>

#ifdef CRYSTAL_USE_OLD_TYPEINFO
    AssociateBaseTypes(Crystal::Object, 0);
    AssociateBaseTypes(Crystal::Event, 1, CLASS(Crystal::Object));
    AssociateBaseTypes(Crystal::EventHandler, 1, CLASS(Crystal::Object));
#endif
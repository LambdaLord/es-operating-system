// Generated by esidl (r1745).
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_CLIENTRECTLISTIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_CLIENTRECTLISTIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/views/ClientRectList.h>

#include <org/w3c/dom/views/ClientRect.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class ClientRectListImp : public ObjectMixin<ClientRectListImp>
{
public:
    // ClientRectList
    unsigned int getLength() __attribute__((weak));
    views::ClientRect item(unsigned int index) __attribute__((weak));
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return views::ClientRectList::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return views::ClientRectList::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_CLIENTRECTLISTIMP_H_INCLUDED
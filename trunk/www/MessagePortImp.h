// Generated by esidl (r1745).
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_MESSAGEPORTIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_MESSAGEPORTIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/html/MessagePort.h>
#include "EventTargetImp.h"

#include <org/w3c/dom/events/EventTarget.h>
#include <org/w3c/dom/html/Function.h>
#include <org/w3c/dom/html/MessagePort.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class MessagePortImp : public ObjectMixin<MessagePortImp, EventTargetImp>
{
public:
    // MessagePort
    void postMessage(Any message) __attribute__((weak));
    void postMessage(Any message, html::MessagePortArray ports) __attribute__((weak));
    void start() __attribute__((weak));
    void close() __attribute__((weak));
    html::Function getOnmessage() __attribute__((weak));
    void setOnmessage(html::Function onmessage) __attribute__((weak));
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return html::MessagePort::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return html::MessagePort::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_MESSAGEPORTIMP_H_INCLUDED
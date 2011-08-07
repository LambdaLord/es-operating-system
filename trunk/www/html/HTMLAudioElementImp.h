// Generated by esidl (r1752).
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_HTMLAUDIOELEMENTIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_HTMLAUDIOELEMENTIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/html/HTMLAudioElement.h>
#include "HTMLMediaElementImp.h"

#include <org/w3c/dom/html/HTMLAudioElement.h>
#include <org/w3c/dom/html/HTMLMediaElement.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class HTMLAudioElementImp : public ObjectMixin<HTMLAudioElementImp, HTMLMediaElementImp>
{
public:
    HTMLAudioElementImp(DocumentImp* ownerDocument) :
        ObjectMixin(ownerDocument, u"audio") {
    }
    HTMLAudioElementImp(HTMLAudioElementImp* org, bool deep) :
        ObjectMixin(org, deep) {
    }

    // HTMLAudioElement
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return html::HTMLAudioElement::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return html::HTMLAudioElement::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_HTMLAUDIOELEMENTIMP_H_INCLUDED
// Generated by esidl (r1745).
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_HTMLMAPELEMENTIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_HTMLMAPELEMENTIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/html/HTMLMapElement.h>
#include "HTMLElementImp.h"

#include <org/w3c/dom/html/HTMLElement.h>
#include <org/w3c/dom/html/HTMLCollection.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class HTMLMapElementImp : public ObjectMixin<HTMLMapElementImp, HTMLElementImp>
{
public:
    // HTMLMapElement
    std::u16string getName() __attribute__((weak));
    void setName(std::u16string name) __attribute__((weak));
    html::HTMLCollection getAreas() __attribute__((weak));
    html::HTMLCollection getImages() __attribute__((weak));
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return html::HTMLMapElement::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return html::HTMLMapElement::getMetaData();
    }
    HTMLMapElementImp(DocumentImp* ownerDocument) :
        ObjectMixin(ownerDocument, u"map") {
    }
    HTMLMapElementImp(HTMLMapElementImp* org, bool deep) :
        ObjectMixin(org, deep) {
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_HTMLMAPELEMENTIMP_H_INCLUDED
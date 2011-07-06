/*
 * Copyright 2010, 2011 Esrille Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NODELIST_IMP_H
#define NODELIST_IMP_H

#include <Object.h>
#include <org/w3c/dom/NodeList.h>

#include <org/w3c/dom/Node.h>

namespace org { namespace w3c { namespace dom { namespace bootstrap {

class NodeListImp : public ObjectMixin<NodeListImp>
{
    Node node;
    // TODO: add more constraints for getElementsByTagName(), etc.

public:
    NodeListImp(Node node);

    // NodeList
    virtual Node item(unsigned int index) __attribute__((weak));
    virtual unsigned int getLength() __attribute__((weak));
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return NodeList::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return NodeList::getMetaData();
    }
};


}}}}  // org::w3c::dom::bootstrap

#endif  // NODELIST_IMP_H

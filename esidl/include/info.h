/*
 * Copyright 2008-2010 Google Inc.
 * Copyright 2007 Nintendo Co., Ltd.
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

#ifndef ESIDL_INFO_H_INCLUDED
#define ESIDL_INFO_H_INCLUDED

#include <string>
#include "esidl.h"
#include "expr.h"
#include "formatter.h"
#include "reflect.h"

// Generate the string-encoded interface information for reflection
class Info : public Visitor, public Formatter
{
    const Node* currentNode;
    bool constructorMode;
    unsigned offset;

    void visitInterfaceElement(const Interface* interface, Node* element)
    {
        if (element->isSequence(interface) ||
            element->isNative(interface) ||
            element->isTypedef(interface) ||
            element->isInterface(interface))  // Do not process Constructor
        {
            return;
        }
        writeln("");
        writetab();
        write("/* %u */ ", offset);
        element->accept(this);
    }

public:
    Info(Formatter* f) :
        Formatter(f),
        currentNode(0),
        constructorMode(false),
        offset(0)
    {
        flush();
    }

    virtual void at(const Module* node)
    {
        // Info{} visiter should be applied for interfaces.
    }

    virtual void at(const Attribute* node)
    {
        write("\"%s\"", node->getMetaGetter().c_str());
        offset += node->getMetaGetter().length();
        if (!node->isReadonly() || node->isPutForwards() || node->isReplaceable())
        {
            writeln("");
            writetab();
            write("/* %u */ ", offset);
            write("\"%s\"", node->getMetaSetter().c_str());
            offset += node->getMetaSetter().length();
        }
    }

    virtual void at(const OpDcl* node)
    {
        for (int i = 0; i < node->getMethodCount(); ++i)
        {
            if (i != 0)
            {
                writeln("");
                writetab();
                write("/* %u */ ", offset);
            }
            if (constructorMode)
            {
                write("\"%c%s\"", Reflect::kConstructor, node->getMetaOp(i).c_str() + 1);
            }
            else
            {
                write("\"%c%s\"", Reflect::kOperation, node->getMetaOp(i).c_str() + 1);
            }
            offset += node->getMetaOp(i).length();
        }
    }

    virtual void at(const Interface* node)
    {
        if (node->isLeaf())
        {
            return;
        }

        currentNode = node;
        offset = 0;

        writeln("");
        writetab();
        write("/* %u */ ", offset);
        write("\"%s\"", node->getMeta().c_str());

        offset += node->getMeta().length();

        // Expand supplementals
        std::list<const Interface*> interfaceList;
        node->collectSupplementals(&interfaceList);
        for (std::list<const Interface*>::const_iterator i = interfaceList.begin();
             i != interfaceList.end();
             ++i)
        {
            const Node* saved = currentNode;
            for (NodeList::iterator j = (*i)->begin(); j != (*i)->end(); ++j)
            {
                currentNode = *i;
                visitInterfaceElement(*i, *j);
            }
            currentNode = saved;
        }

        if (Interface* constructor = node->getConstructor())
        {
            // Process constructors.
            constructorMode = true;
            for (NodeList::iterator i = constructor->begin();
                 i != constructor->end();
                 ++i)
            {
                visitInterfaceElement(node, *i);
            }
            constructorMode = false;
        }

        flush();
    }

    virtual void at(const ConstDcl* node)
    {
        write("\"%s\"", node->getMeta().c_str());
        offset += node->getMeta().length();
    }

    virtual void at(const Member* node)
    {
        assert(node->isTypedef(node->getParent()));
        node->getSpec()->accept(this);
    }
};

#endif  // ESIDL_INFO_H_INCLUDED

/*
 * Copyright 2008 Google Inc.
 * Copyright 2006, 2007 Nintendo Co., Ltd.
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

#include <errno.h>
#include <string.h>
#include <es/clsid.h>
#include <es/exception.h>
#include <es/synchronized.h>
#include "loopback.h"

/*
 *  data format
 *  in the ring buffer
 *
 *  :              :
 *  |              |
 *  +--------------+
 *  |  size (int)  |
 *  + - -  - - - - +
 *  |              |
 *  |  data        |
 *  : (size bytes) :
 *  :              :
 *  :              :
 *  |              |
 *  |              |
 *  |              |
 *  +--------------+
 *  |              |
 *  :              :
 */

//
// IStream
//
long long Loopback::
getPosition()
{
    return 0;
}

void Loopback::
setPosition(long long pos)
{
}

// Gets the number of filled bytes in this ring buffer.
long long Loopback::
getSize()
{
    Monitor::Synchronized method(monitor);
    return ring.getUsed();
}

void Loopback::
setSize(long long size)
{
}

int Loopback::
read(void* dst, int count)
{
    Monitor::Synchronized method(monitor);

    int size;
    int ret;
    while ((ret = ring.peek(&size, sizeof size)) == 0)
    {
        monitor.wait();
    }

    if (ret < 0 || count < ret)
    {
        return -1;
    }

    ring.read(&size, sizeof size);
    ret = ring.read(dst, size);

    monitor.notifyAll();
    return ret;
}

int Loopback::
read(void* dst, int count, long long offset)
{
    return -1;
}

int Loopback::
write(const void* src, int count)
{
    Monitor::Synchronized method(monitor);

    while (ringSize - ring.getUsed() < sizeof(int) + count)
    {
        // no enough space in the ring buffer.
        monitor.wait();
    }

    ring.write(&count, sizeof(int));
    int ret = ring.write(src, count);

    monitor.notifyAll();
    return ret;
}

int Loopback::
write(const void* src, int count, long long offset)
{
    return -1;
}

void Loopback::flush()
{
}

//
// IInterface
//

void* Loopback::
queryInterface(const Guid& riid)
{
    void* objectPtr;
    if (riid == IStream::iid())
    {
        objectPtr = static_cast<IStream*>(this);
    }
    else if (riid == INetworkInterface::iid())
    {
        objectPtr = static_cast<INetworkInterface*>(this);
    }
    else if (riid == IInterface::iid())
    {
        objectPtr = static_cast<IStream*>(this);
    }
    else
    {
        return NULL;
    }
    static_cast<IInterface*>(objectPtr)->addRef();
    return objectPtr;
}

unsigned int Loopback::
addRef(void)
{
    return ref.addRef();
}

unsigned int Loopback::
release(void)
{
    unsigned int count = ref.release();
    if (count == 0)
    {
        delete this;
        return 0;
    }
    return count;
}

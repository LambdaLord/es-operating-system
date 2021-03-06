/*
 * Copyright 2008, 2009 Google Inc.
 * Copyright 2006 Nintendo Co., Ltd.
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

#include <new>
#include <stdlib.h>
#include <es.h>
#include <es/handle.h>
#include "vdisk.h"
#include "partition.h"

#define TEST(exp)                           \
    (void) ((exp) ||                        \
            (esPanic(__FILE__, __LINE__, "\nFailed test " #exp), 0))

es::DiskManagement::Geometry VDiskGeometry;

static void SetData(u8* buf, long long size)
{
    buf[size-1] = 0;
    while (--size)
    {
        *buf++ = 'a' + size % 26;
    }
}

void PrintPartitions(es::Context* context)
{
    char name[16];
    es::DiskManagement::Partition params;
    esReport("boot type offset   size\n");
    Handle<es::Iterator> iter = context->list("");
    Handle<es::Binding> binding;
    while ((binding = iter->next()))
    {
        Handle<es::DiskManagement> diskManagement = binding->getObject();
        TEST(diskManagement);
        diskManagement->getLayout(&params);
        TEST(0 < binding->getName(name, sizeof(name)));
        esReport("%02x   %02x   %08llx %08llx %s\n",
                 params.bootIndicator,
                 params.partitionType,
                 params.startingOffset,
                 params.partitionLength,
                 name);

        Handle<es::Stream> stream = context->lookup(name);
        TEST(stream);
        long long size;
        size = stream->getSize();
        TEST(params.partitionLength == size);
        TEST(params.bootIndicator == 0x00 || params.bootIndicator == 0x80);
        TEST(params.partitionType != 0x00);
    }
    esReport("\n");
}

void CheckGeometry(Handle<es::DiskManagement> dm)
{
    es::DiskManagement::Geometry geometry;
    dm->getGeometry(&geometry); // throw exception when error occurs.
#ifdef VERBOSE
    esReport("Geometry\n");
    esReport("  heads           %u\n", geometry.heads);
    esReport("  cylinders       %u\n", geometry.cylinders);
    esReport("  sectorsPerTrack %u\n", geometry.sectorsPerTrack);
    esReport("  bytesPerSector  %u\n", geometry.bytesPerSector);
    esReport("  diskSize        %llu\n", geometry.diskSize);
#endif // VERBOSE
    TEST(geometry.heads == VDiskGeometry.heads);
    TEST(geometry.cylinders == VDiskGeometry.cylinders);
    TEST(geometry.sectorsPerTrack == VDiskGeometry.sectorsPerTrack);
    TEST(geometry.bytesPerSector == VDiskGeometry.bytesPerSector);
    TEST(geometry.diskSize == VDiskGeometry.diskSize);
}

void CreatePartition(es::Context* context, const char* name, long long& size, u8 type)
{
    esReport("Create: %s (size %lld, type 0x%02x)\n", name ,size, type);

    Handle<es::Binding> binding;
    binding = context->bind(name, 0);
    TEST(binding);

    Handle<es::Stream> stream = context->lookup(name);
    TEST(stream);
    Handle<es::Stream> object = binding->getObject();
    TEST(stream == object);

    CheckGeometry(stream);

    Handle<es::DiskManagement> diskManagement = stream;
    es::DiskManagement::Partition params;
    diskManagement->getLayout(&params);

    stream->setSize(size);
    size = stream->getSize();

    if (type != 0x05 && type != 0x0f)
    {
        // set the partition type.
        diskManagement->getLayout(&params);
        params.partitionType = type;

        diskManagement->setLayout(&params);
        diskManagement->getLayout(&params);
        TEST(params.partitionType == type);
    }
}

void Test(es::Context* context)
{
    Handle<es::Binding> binding;
    Handle<es::Stream> stream;

    long long size0 = 8 * 1024 * 1024LL;
    CreatePartition(context, "partition0", size0, 0x01);

    long long size1 = 24 * 1024 * 1024LL;
    CreatePartition(context, "extended", size1, 0x05);

    long long size2 = 8 * 1024 * 1024LL;
    CreatePartition(context, "logical0", size2, 0x04);

    long long size3 = 8 * 1024 * 1024LL;
    CreatePartition(context, "logical1", size3, 0x04);

    long long size4 = 8 * 1024 * 1024LL;
    CreatePartition(context, "logical2", size4, 0x04);

    stream = context->lookup("extended");
    Handle<es::DiskManagement> dm = stream;

    es::DiskManagement::Geometry geometry;
    dm->getGeometry(&geometry);
    size0 = stream->getSize();

    // check the sizes of partitions except for the last partition
    // are not configurable.
    stream = context->lookup("logical0");
    stream->setSize(size2 + 1024 * 1024LL);

    long long size;
    size = stream->getSize();
    TEST(size2 == size);

    // the last partition.
    stream = context->lookup("logical2");
    stream->setSize(size4 + 1024 * 1024LL);

    size = stream->getSize();

    TEST(size4 < size);

    // write data.
    long long ret;
    u8* writeBuf = new u8[size];
    SetData(writeBuf, size);
    ret = stream->write(writeBuf, size, 0);
    TEST(ret == size);
    stream->flush();
    // read data.
    u8* readBuf = new u8[size];
    memset(readBuf, 0, size);
    ret = stream->read(readBuf, size, 0);
    TEST(ret == size);
    TEST(memcmp(readBuf, writeBuf, size) == 0);

    delete [] writeBuf;
    delete [] readBuf;

    // check logical partitions except for the last partition cannot be removed.
    TEST(context->unbind("logical1") < 0);
    TEST(context->unbind("logical0") < 0);
    TEST(context->unbind("extended") < 0);

    stream = context->lookup("extended");
    TEST(stream);
    stream = context->lookup("logical0");
    TEST(stream);
    stream = context->lookup("logical1");
    TEST(stream);
    stream = context->lookup("logical2");
    TEST(stream);
}

void Init(es::Context* context)
{
    // remove all partitions.
    esReport("Remove all partitions.\n");
    context->unbind("partition0");
    context->unbind("partition1");
    context->unbind("partition2");
    context->unbind("partition3");

    char name[16];
    int id = 0;
    sprintf(name, "logical%u", id);

    Handle<es::Stream> stream;
    Handle<es::Binding> binding;
    while (stream = context->lookup(name))
    {
        ++id;
        sprintf(name, "logical%u", id);
    }

    while (id)
    {
        --id;
        sprintf(name, "logical%u", id);
        TEST(context->unbind(name) == 0);
    }

    context->unbind("extended0");

    // check
    stream = context->lookup("partition0");
    TEST(!stream);
    stream = context->lookup("partition1");
    TEST(!stream);
    stream = context->lookup("partition2");
    TEST(!stream);
    stream = context->lookup("partition3");
    TEST(!stream);
    stream = context->lookup("extended0");
    TEST(!stream);
}

int main(int argc, char* argv[])
{
    Object* ns = 0;
    esInit(&ns);

    Handle<es::Stream> disk = new VDisk(static_cast<char*>("fat16_32MB.img"));
    Handle<es::DiskManagement> dm = disk;
    dm->getGeometry(&VDiskGeometry);

    Handle<es::Partition> partition = new PartitionContext();
    TEST(partition);

    // mount
    TEST(partition->mount(disk) == 0);
    {
        Handle<es::Context> context = partition;
        TEST(context);

        Init(context);

        Test(context);

        // show results.
        esReport("\nPartition Entry Table\n");
        PrintPartitions(context);
    }

    // unmount
    TEST(partition->unmount() == 0);
    partition = 0;

    partition = new PartitionContext();
    TEST(partition);
    TEST(partition->mount(disk) == 0);
    {
        Handle<es::Context> context = partition;
        // check
        Handle<es::Stream> stream;
        TEST(stream = context->lookup("partition0"));
        TEST(!(stream = context->lookup("partition1")));
        TEST(!(stream = context->lookup("partition2")));
        TEST(stream = context->lookup("extended"));
        TEST(stream = context->lookup("logical0"));
        TEST(stream = context->lookup("logical1"));
        TEST(stream = context->lookup("logical2"));
    }
    TEST(partition->unmount() == 0);

    esReport("done.\n\n");
}

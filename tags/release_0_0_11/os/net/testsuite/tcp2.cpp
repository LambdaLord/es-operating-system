/*
 * Copyright (c) 2006, 2007
 * Nintendo Co., Ltd.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Nintendo makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#include <string.h>
#include <es.h>
#include <es/endian.h>
#include <es/handle.h>
#include <es/list.h>
#include <es/base/IStream.h>
#include <es/device/INetworkInterface.h>
#include <es/naming/IContext.h>
#include <es/net/ISocket.h>
#include <es/net/IInternetConfig.h>
#include <es/net/IResolver.h>
#include <es/net/arp.h>

#define TEST(exp)                           \
    (void) ((exp) ||                        \
            (esPanic(__FILE__, __LINE__, "\nFailed test " #exp), 0))

extern int esInit(IInterface** nameSpace);
extern void esRegisterInternetProtocol(IContext* context);

char data[8000];
int len[4];

int main()
{
    IInterface* root = NULL;
    esInit(&root);
    Handle<IContext> context(root);

    esRegisterInternetProtocol(context);

    // Create resolver object
    Handle<IResolver> resolver = context->lookup("network/resolver");

    // Create internet config object
    Handle<IInternetConfig> config = context->lookup("network/config");

    // Setup DIX interface
    Handle<INetworkInterface> ethernetInterface = context->lookup("device/ethernet");
    ethernetInterface->start();
    int dixID = config->addInterface(ethernetInterface);
    esReport("dixID: %d\n", dixID);

    ASSERT(config->getScopeID(ethernetInterface) == dixID);

    // Register host address (192.168.2.40)
    InAddr addr = { htonl(192 << 24 | 168 << 16 | 2 << 8 | 40) };
    Handle<IInternetAddress> host = resolver->getHostByAddress(&addr.addr, sizeof addr, dixID);
    config->addAddress(host, 16);
    esSleep(90000000);  // Wait for the host address to be settled.

    // Register a default router (192.168.2.1)
    InAddr addrRouter = { htonl(192 << 24 | 168 << 16 | 2 << 8 | 1) };
    Handle<IInternetAddress> router = resolver->getHostByAddress(&addrRouter.addr, sizeof addr, dixID);
    config->addRouter(router);

    // chargen server (192.168.2.20)
    InAddr addrChargen = { htonl(192 << 24 | 168 << 16 | 2 << 8 | 20) };
    Handle<IInternetAddress> chargen = resolver->getHostByAddress(&addrChargen.addr, sizeof addr, dixID);

    Handle<IInternetAddress> any = resolver->getHostByAddress(&InAddrAny.addr, sizeof(InAddr), 0);

    // Test bind and connect operations
    Handle<ISocket> socket = any->socket(AF_INET, ISocket::Stream, 0);
    socket->setReceiveBufferSize(4096);
    socket->setSendBufferSize(4096);
    socket->connect(chargen, 19);

    int pos = 0;
    for (int i = 0; i < 4; ++i)
    {
        int result = socket->read(data + pos, 2000);
        if (result <= 0)
        {
            break;
        }
        len[i] = result;
        pos += len[i];
        esSleep(10000000);
    }

    esSleep(30000000);

    // Test close operation
    socket->close();

    esSleep(30000000);

    ethernetInterface->stop();

    pos = 0;
    for (int i = 0; i < 4; ++i)
    {
        esReport("len: %d\n", len[i]);
        esDump(data + pos, len[i]);
        pos += len[i];
    }
    esReport("done.\n");
}
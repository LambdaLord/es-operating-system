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

#include <new>
#include "inet4.h"

u16 InReceiver::identification;

InFamily::InFamily() :
    scopeMux(&scopeAccessor, &scopeFactory),
    inReceiver(this),
    inMux(&inAccessor, &inFactory),
    icmpMux(&icmpAccessor, &icmpFactory),
    echoReplyMux(&echoReplyAccessor, &echoReplyFactory),
    echoRequestReceiver(0),
    echoRequestFactory(&echoRequestAdapter),
    echoRequestMux(&echoRequestAccessor, &echoRequestFactory),

    igmpReceiver(this),
    igmpFactory(&igmpAdapter),
    igmpMux(&igmpAccessor, &igmpFactory),

    udpRemoteAddressFactory(&datagramProtocol),
    udpRemoteAddressMux(&udpRemoteAddressAccessor, &udpRemoteAddressFactory),
    udpRemotePortFactory(&udpRemoteAddressMux),
    udpRemotePortMux(&udpRemotePortAccessor, &udpRemotePortFactory),
    udpLocalAddressFactory(&udpRemotePortMux),
    udpLocalAddressMux(&udpLocalAddressAccessor, &udpLocalAddressFactory),
    udpLocalPortFactory(&udpLocalAddressMux),
    udpLocalPortMux(&udpLocalPortAccessor, &udpLocalPortFactory),
    udpLast(49152),
    udpUnreachReceiver(&unreachProtocol),

    streamReceiver(&tcpProtocol),
    tcpRemoteAddressFactory(&streamProtocol),
    tcpRemoteAddressMux(&tcpRemoteAddressAccessor, &tcpRemoteAddressFactory),
    tcpRemotePortFactory(&tcpRemoteAddressMux),
    tcpRemotePortMux(&tcpRemotePortAccessor, &tcpRemotePortFactory),
    tcpLocalAddressFactory(&tcpRemotePortMux),
    tcpLocalAddressMux(&tcpLocalAddressAccessor, &tcpLocalAddressFactory),
    tcpLocalPortFactory(&tcpLocalAddressMux),
    tcpLocalPortMux(&tcpLocalPortAccessor, &tcpLocalPortFactory),
    tcpLast(49152),

    reassReceiver(&inProtocol, &timeExceededProtocol, &reassAdapter),
    reassIdFactory(&reassAdapter),
    reassIdMux(&reassIdAccessor, &reassIdFactory),
    reassRemoteAddressFactory(&reassIdMux),
    reassRemoteAddressMux(&reassRemoteAddressAccessor, &reassRemoteAddressFactory),
    reassLocalAddressFactory(&reassRemoteAddressMux),
    reassLocalAddressMux(&reassLocalAddressAccessor, &reassLocalAddressFactory),

    addressAny(InAddrAny, Inet4Address::statePreferred),
    addressAllRouters(InAddrAllRouters, Inet4Address::stateNonMember),

    arpFamily(this)
{
    inProtocol.setReceiver(&inReceiver);
    icmpProtocol.setReceiver(&icmpReceiver);
    echoRequestAdapter.setReceiver(&echoRequestReceiver);
    igmpProtocol.setReceiver(&igmpReceiver);
    udpProtocol.setReceiver(&udpReceiver);

    datagramProtocol.setReceiver(&datagramReceiver);
    tcpProtocol.setReceiver(&tcpReceiver);
    streamProtocol.setReceiver(&streamReceiver);
    unreachProtocol.setReceiver(&unreachReceiver);
    timeExceededProtocol.setReceiver(&timeExceededReceiver);

    Conduit::connectAA(&scopeMux, &inProtocol);
    Conduit::connectBA(&inProtocol, &inMux);
    Conduit::connectBA(&inMux, &icmpProtocol, reinterpret_cast<void*>(IPPROTO_ICMP));
    Conduit::connectBA(&inMux, &igmpProtocol, reinterpret_cast<void*>(IPPROTO_IGMP));
    Conduit::connectBA(&inMux, &udpProtocol, reinterpret_cast<void*>(IPPROTO_UDP));
    Conduit::connectBA(&inMux, &tcpProtocol, reinterpret_cast<void*>(IPPROTO_TCP));
    Conduit::connectBA(&inMux, &reassProtocol, reinterpret_cast<void*>(IPPROTO_FRAGMENT));

    // ICMP
    Conduit::connectBA(&icmpProtocol, &icmpMux);
    Conduit::connectBA(&icmpMux, &echoReplyMux, reinterpret_cast<void*>(ICMPHdr::EchoReply));
    Conduit::connectBA(&icmpMux, &echoRequestMux, reinterpret_cast<void*>(ICMPHdr::EchoRequest));
    Conduit::connectBA(&icmpMux, &unreachProtocol, reinterpret_cast<void*>(ICMPHdr::Unreach));
    Conduit::connectBA(&icmpMux, &timeExceededProtocol, reinterpret_cast<void*>(ICMPHdr::TimeExceeded));
    unreachProtocol.setB(&inProtocol);      // loop
    timeExceededProtocol.setB(&inProtocol); // loop

    // IGMP
    igmpAdapter.setReceiver(&addressAny);
    Conduit::connectBA(&igmpProtocol, &igmpMux);

    // UDP
    udpRemoteAddressFactory.setReceiver(&udpUnreachReceiver);
    udpRemotePortFactory.setReceiver(&udpUnreachReceiver);
    udpLocalAddressFactory.setReceiver(&udpUnreachReceiver);
    udpLocalPortFactory.setReceiver(&udpUnreachReceiver);
    Conduit::connectBA(&udpProtocol, &udpLocalPortMux);

    // TCP
    tcpRemoteAddressFactory.setReceiver(&streamReceiver);
    tcpRemotePortFactory.setReceiver(&streamReceiver);
    tcpLocalAddressFactory.setReceiver(&streamReceiver);
    tcpLocalPortFactory.setReceiver(&streamReceiver);
    Conduit::connectBA(&tcpProtocol, &tcpLocalPortMux);

    // Fragment Reassemble
    reassAdapter.setReceiver(&reassReceiver);
    reassIdFactory.setReceiver(&reassFactoryReceiver);
    reassRemoteAddressFactory.setReceiver(&reassFactoryReceiver);
    reassLocalAddressFactory.setReceiver(&reassFactoryReceiver);
    Conduit::connectBA(&reassProtocol, &reassLocalAddressMux);

    Socket::addAddressFamily(this);
}

Inet4Address* InFamily::getAddress(InAddr addr, int scopeID)
{
    ASSERT(0 <= scopeID && scopeID < Socket::INTERFACE_MAX);

    Inet4Address* address;
    try
    {
        address = addressTable[scopeID].get(addr);
    }
    catch (SystemException<ENOENT>)
    {
        if (scopeID == 0)
        {
            address = 0;
        }
        else
        {
            try
            {
                address = addressTable[0].get(addr);
            }
            catch (SystemException<ENOENT>)
            {
                address = 0;
            }
        }
    }
    if (address)
    {
        address->addRef();
    }
    return address;
}

void InFamily::addAddress(Inet4Address* address)
{
    int scopeID = address->getScopeID();
    addressTable[scopeID].add(address->getAddress(), address);
    address->addRef();
    address->inFamily = this;
}

void InFamily::removeAddress(Inet4Address* address)
{
    int scopeID = address->getScopeID();
    addressTable[scopeID].remove(address->getAddress());
    address->inFamily = 0;
    address->release();
}

Inet4Address* InFamily::onLink(InAddr addr, int scopeID)
{
    Tree<void*, Conduit*>::Node* node;
    Tree<void*, Conduit*>::Iterator iter = echoRequestMux.list();
    while ((node = iter.next()))
    {
        Conduit* conduit = node->getValue();
        ICMPEchoRequestReceiver* receiver = dynamic_cast<ICMPEchoRequestReceiver*>(conduit->getReceiver());
        ASSERT(receiver);
        Inet4Address* local = receiver->getAddress();
        ASSERT(local);
        if (local->getPrefix() &&
            IN_IS_ADDR_IN_NET(addr, local->getAddress(), local->getMask()) &&
            (scopeID == 0 || scopeID == local->getScopeID()))
        {
            return local;
        }
        local->release();
    }
    return 0;
}

Inet4Address* InFamily::getNextHop(Inet4Address* dst)
{
    int scopeID = dst->getScopeID();
    if (scopeID == 0)
    {
        Inet4Address* router = routerList.getRouter();
        if (router)
        {
            return router;
        }
    }

    dst->addRef();
    return dst;
}

Inet4Address* InFamily::selectSourceAddress(Inet4Address* dst)
{
    if (!dst)
    {
        return 0;
    }

    if (dst->isLoopback())
    {
        return getAddress(InAddrLoopback, 1);
    }

    Inet4Address* src = 0;
    src = onLink(dst->getAddress(), dst->getScopeID());
    if (src)
    {
        return src;
    }

    // XXX Check destination cache

    int scopeID = dst->getScopeID();
    if (scopeID == 0)
    {
        Inet4Address* router = routerList.getRouter();
        if (router)
        {
            src = onLink(router->getAddress(), router->getScopeID());
            router->release();
            if (src)
            {
                return src;
            }
        }
        scopeID = 2;    // default
    }

    // Look up preferred address of the same scope ID.
    Tree<InAddr, Inet4Address*>::Node* node;
    Tree<InAddr, Inet4Address*>::Iterator iter = addressTable[scopeID].begin();
    while ((node = iter.next()))
    {
        Inet4Address* address = node->getValue();
        if (address->isPreferred())
        {
            src = address;
            src->addRef();
            break;
        }
    }

    if (!src)
    {
        // Use 0.0.0.0 as default XXX
    }

    return src;
}

bool InFamily::isReachable(Inet4Address* dst, long long timeout)
{
    Handle<Inet4Address> src = selectSourceAddress(dst);
    if (!src)
    {
        return false;
    }

    Adapter* adapter = new Adapter;
    ICMPEchoReplyReceiver* receiver = new ICMPEchoReplyReceiver(adapter, dst);
    adapter->setReceiver(receiver);
    Conduit::connectBA(&echoReplyMux, adapter, dst);

    // Send ICMP Echo request to dst
    int pos = 14 + 60;      // XXX Assume MAC, IPv4
    int len = sizeof(ICMPEcho) + 10;
    Handle<InetMessenger> m = new InetMessenger(&InetReceiver::output, pos + len, pos);
    ICMPEcho* icmphdr = reinterpret_cast<ICMPEcho*>(m->fix(len));
    memmove(&icmphdr[1], "0123456789", 10);
    icmphdr->type = ICMPHdr::EchoRequest;
    icmphdr->code = 0;
    icmphdr->id = 0;    // XXX
    icmphdr->seq = 0;   // XXX

    m->setRemote(dst);
    m->setLocal(src);
    m->setType(IPPROTO_ICMP);

    Visitor v(m);
    adapter->accept(&v);

    receiver->wait(timeout);

    bool replied = receiver->isReplied();

    echoReplyMux.removeB(dst);
    delete adapter;
    delete receiver;

    return replied;
}

void InFamily::joinGroup(Inet4Address* address)
{
    ASSERT(address->isMulticast());

    InetMessenger m;
    m.setLocal(address);
    Installer installer(&m);
    igmpMux.accept(&installer, &igmpProtocol);

    // Add address to NIC mcast table
    int scopeID = address->getScopeID();
    Interface* interface = Socket::getInterface(scopeID);
    if (interface)
    {
        u8 mac[6];
        address->getMacAddress(mac);
        interface->addMulticastAddress(mac);
    }
}

void InFamily::leaveGroup(Inet4Address* address)
{
    ASSERT(address->isMulticast());

    Adapter* adapter = dynamic_cast<Adapter*>(address->getAdapter());
    if (adapter)
    {
        InetMessenger m;
        m.setLocal(address);
        Uninstaller uninstaller(&m);
        adapter->accept(&uninstaller);
        address->release();
    }

    // Remove address from NIC mcast table
    int scopeID = address->getScopeID();
    Interface* interface = Socket::getInterface(scopeID);
    if (interface)
    {
        u8 mac[6];
        address->getMacAddress(mac);
        interface->removeMulticastAddress(mac);
    }
}

s16 InReceiver::
checksum(const InetMessenger* m, int hlen)
{
    s32 sum = m->sumUp(hlen);
    while (sum >> 16)
    {
        sum = (sum & 0xffff) + (sum >> 16);
    }
    return ~sum;
}

bool InReceiver::
input(InetMessenger* m, Conduit* c)
{
    Handle<Inet4Address> addr;

    IPHdr* iphdr = static_cast<IPHdr*>(m->fix(sizeof(IPHdr)));
    if (!iphdr)
    {
        return false;
    }
    int hlen = iphdr->getHdrSize();
    if (m->getLength() < hlen || checksum(m, hlen) != 0)
    {
        return false;
    }

    int scopeID = m->getScopeID();

    addr = inFamily->getAddress(iphdr->dst, scopeID);
    if (!addr)
    {
        return false;
    }
    m->setLocal(addr);

    addr = inFamily->getAddress(iphdr->src, scopeID);
    if (!addr)
    {
        Handle<Inet4Address> onLink;
        if (IN_IS_ADDR_LOOPBACK(iphdr->src))
        {
            return false;
        }
        else if (IN_IS_ADDR_MULTICAST(iphdr->src))
        {
            addr = new Inet4Address(iphdr->src, Inet4Address::stateNonMember, scopeID);
        }
        else if (onLink = inFamily->onLink(iphdr->src))
        {
            addr = new Inet4Address(iphdr->src, Inet4Address::stateInit, onLink->getScopeID());
        }
        else
        {
            addr = new Inet4Address(iphdr->src, Inet4Address::stateDestination, 0);
        }
        inFamily->addAddress(addr);
    }
    m->setRemote(addr);

    if (iphdr->getOffset() == 0 && !iphdr->moreFragments())
    {
        m->setType(iphdr->proto);
    }
    else
    {
        // RFC 1858
        if (iphdr->proto == IPPROTO_TCP && iphdr->getOffset() == 8)
        {
            return false;
        }

        m->setType(IPPROTO_FRAGMENT);
        int id = iphdr->getId();
        if (id == 0)
        {
            id = 65536;
        }
        m->setRemotePort(id);
    }
    m->savePosition();
    m->movePosition(iphdr->getHdrSize());

    return true;
}

bool InReceiver::
output(InetMessenger* m, Conduit* c)
{
    Handle<Address> addr;

    long len = m->getLength();
    len += sizeof(IPHdr);
    if (65535 < len)
    {
        // XXX Return an error code to the upper layers.
        return false;
    }

    // Add IPHdr
    m->movePosition(-sizeof(IPHdr));
    m->savePosition();
    IPHdr* iphdr = static_cast<IPHdr*>(m->fix(sizeof(IPHdr)));
    iphdr->verlen = 0x45;
    iphdr->tos = 0;
    iphdr->len = htons(len);    // octets in header and data
    iphdr->id = htons(++identification);
    iphdr->frag = 0;
    iphdr->ttl = 64;
    iphdr->proto = m->getType();
    iphdr->sum = 0;
    addr = m->getLocal();
    addr->getAddress(&iphdr->src, sizeof(InAddr));
    addr = m->getRemote();
    addr->getAddress(&iphdr->dst, sizeof(InAddr));
    iphdr->sum = checksum(m, iphdr->getHdrSize());
    m->setType(AF_INET);

    int mtu = addr->getPathMTU();
    if (mtu < m->getLength())
    {
        if (iphdr->dontFragment())
        {
            // XXX Notify an error
            return false;
        }

        // Fragmentation Procedure [RFC 791]
        fragment(m, mtu, m->getRemote()->getNextHop());
        return false;
    }

    // Set the remote address to the next hop router address
    // if necessary.
    m->setRemote(m->getRemote()->getNextHop());

    return true;
}

bool InReceiver::
error(InetMessenger* m, Conduit* c)
{
    IPHdr* iphdr = static_cast<IPHdr*>(m->fix(sizeof(IPHdr)));

    // Reverse src and dst
    Handle<Inet4Address> addr;
    addr = inFamily->getAddress(iphdr->src, m->getScopeID());
    m->setLocal(addr);
    addr = inFamily->getAddress(iphdr->dst, m->getScopeID());
    m->setRemote(addr);

    return true;
}

void InReceiver::
fragment(const InetMessenger* m, int mtu, Address* nextHop)
{
    Handle<Inet4Address> addr;

    IPHdr* org = static_cast<IPHdr*>(m->fix(sizeof(IPHdr)));
    int hlen = org->getHdrSize();
    int offset = ((mtu - hlen) & ~7);

    //
    // Copy the first NFB*8 data octets
    //
    int pos = 14;  // XXX Assume MAC
    int len = hlen + offset;
    Handle<InetMessenger> d = new InetMessenger(&InetReceiver::output, pos + len, pos);
    memmove(d->fix(len), m->fix(len), len);

    // Correct the header: MF <- 1, TL <- (IHL*4)+(NFB*8)
    IPHdr* frag = static_cast<IPHdr*>(d->fix(sizeof(IPHdr)));
    frag->setSize(len);
    frag->frag = htons(IPHdr::MoreFragments);
    frag->sum = 0;
    frag->sum = checksum(d, frag->getHdrSize());

    d->setType(AF_INET);
    d->setRemote(nextHop);
    addr = m->getLocal();
    d->setLocal(addr);

    esReport("frag size = %d\n", frag->getSize());
    Visitor v(d);
    inFamily->scopeMux.accept(&v, &inFamily->inProtocol);

    //
    // Selectively copy the internet header options
    //
    u8 option[IPHdr::MaxHdrSize - IPHdr::MinHdrSize];
    u8* opt = (u8*) &org[1];
    int optlen = org->getHdrSize() - sizeof(IPHdr);
    ASSERT(0 <= optlen);
    u8* ptr = option;
    for (int i = 0; i < optlen && opt[i] != IPOPT_EOOL; i += len)
    {
        switch (opt[i])
        {
          case IPOPT_EOOL:
          case IPOPT_NOP:
            len = 1;
            break;
          default:
            len = opt[i + 1];
            break;
        }
        if (opt[i] & IPOPT_COPIED)
        {
            memmove(ptr, opt + i, len);
            ptr += len;
        }
    }
    optlen = ptr - option;
    while (optlen % 4)
    {
        *ptr++ = IPOPT_EOOL;
        ++optlen;
    }

    //
    // Send the remaining data
    //
    hlen = sizeof(IPHdr) + optlen;
    while (offset < org->getSize() - org->getHdrSize())
    {
        int pos = 14;  // XXX Assume MAC
        len = (mtu - hlen) & ~7;
        len = std::min(len, org->getSize() - org->getHdrSize() - offset);
        Handle<InetMessenger> d = new InetMessenger(&InetReceiver::output, pos + hlen + len, pos);

        IPHdr* frag = static_cast<IPHdr*>(d->fix(sizeof(IPHdr)));
        memmove(frag, org, sizeof(IPHdr));
        memmove(&frag[1], option, optlen);
        memmove((u8*) &frag[1] + optlen, (u8*) org + org->getHdrSize() + offset, len);

        // Correct the header:
        // IHL <- (((OIHL*4)-(length of options not copied))+3)/4;
        // TL <- OTL - NFB*8 - (OIHL-IHL)*4);
        // FO <- OFO + NFB;  MF <- OMF;
        frag->setHdrSize(hlen);
        frag->setSize(hlen + len);
        frag->setOffset(offset);
        if (org->getHdrSize() + offset + len < org->getSize())
        {
            frag->frag |= htons(IPHdr::MoreFragments);
        }

        frag->sum = 0;
        frag->sum = checksum(d, frag->getHdrSize());

        d->setType(AF_INET);
        d->setRemote(nextHop);
        addr = m->getLocal();
        d->setLocal(addr);

        esReport("frag size = %d\n", frag->getSize());
        Visitor v(d);
        inFamily->scopeMux.accept(&v, &inFamily->inProtocol);

        offset += len;
    }
}

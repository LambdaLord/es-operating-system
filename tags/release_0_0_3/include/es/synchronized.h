/*
 * Copyright (c) 2006
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

#ifndef NINTENDO_ES_SYNCHRONIZED_H_INCLUDED
#define NINTENDO_ES_SYNCHRONIZED_H_INCLUDED

/**
 * This template class provides a method to execute synchronized code
 * using a mutual exclusion lock.
 * @param I the class of the mutual exclusion lock.
 */
template<class I>
class Synchronized
{
    I& lock;

    Synchronized& operator=(const Synchronized&);

public:
    /**
     * Constructs a synchronized block using the specified mutual exclusion lock.
     * @param lock the mutual exclusion lock.
     */
    Synchronized(I& lock) : lock(lock)
    {
        lock->lock();
    }
    /**
     * Terminates this synchronized block.
     */
    ~Synchronized()
    {
        lock->unlock();
    }
};

#endif  // NINTENDO_ES_SYNCHRONIZED_H_INCLUDED
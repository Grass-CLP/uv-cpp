// =================================
// Created by Lipson on 21-2-1.
// Email to LipsonChan@yahoo.com
// Copyright (c) 2021 Lipson. All rights reserved.
// Version 1.0
// =================================


#ifndef UV_CPP_SPINMUTEX_HPP
#define UV_CPP_SPINMUTEX_HPP

class SpinMutex
{
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    SpinMutex() = default;
    SpinMutex(const SpinMutex&) = delete;
    SpinMutex& operator= (const SpinMutex&) = delete;

    void lock()
    {
        while(flag.test_and_set(std::memory_order_acquire))
            ;
    }

    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
};

#endif //UV_CPP_SPINMUTEX_HPP

// =================================
// Created by Lipson on 21-1-25.
// Email to LipsonChan@yahoo.com
// Copyright (c) 2021 Lipson. All rights reserved.
// Version 1.0
// =================================


#ifndef UV_CPP_BUFFER_HPP
#define UV_CPP_BUFFER_HPP

#include <stdio.h>
#include <memory.h>

namespace uv {


/**
 * Memory ring buffer, thread no safe
 */

class OrdinalBuffer {
public:
    OrdinalBuffer(size_t size) : buf_size(size), org_size(size) {
        buffer = new char[size];
    }

    ~OrdinalBuffer() {
        _clear();
    }

    bool append(const void *data, size_t size) {
        if (!_reserve_size(size)) return false;
        memcpy(buffer + w_index, data, size);
        w_index += size;

        return true;
    }

    void * read() {
        return buffer + r_index;
    }

    void * write() {
        return buffer + w_index;
    }

    bool resize(size_t size) {
        return _reserve_size(size);
    }

    void * read(size_t size) {
        if (w_index - r_index < size)
            return nullptr;

        auto index = buffer + r_index;
        r_index += size;
        return index;
    }

    void written(size_t size) {
        // no need check (size < buffer - w_index); cause resize will call first
        w_index += size;
    }

    size_t readable_size() {
        return w_index - r_index;
    }

    size_t writable_size() {
        return buf_size - w_index;
    }

    size_t capacity() {
        return buf_size;
    }

protected:
    void _clear() {
        if (buffer) {
            delete[] buffer;
            buffer = nullptr;
        }
    }

    bool _reserve_size(size_t size) {
        // need relarge, dangerous, cause point for reader may be wild when opt_large
        if (r_index + (buf_size - w_index) < size) {
//            return false;   // no large

            _opt_large();
            _reserve_size(size);  // check next
        }

        // need turn
        if (w_index + size > buf_size) {
            _turn();
            return _reserve_size(size);
        }

        return true;
    }

    void _turn() {
        memmove(buffer, buffer + r_index, w_index - r_index);

        w_index = w_index - r_index;
        r_index = 0;
    }

    void _opt_large() {
        char *tmp_buffer = new char[buf_size * 2];
        memcpy(tmp_buffer, buffer + r_index, w_index - r_index);

        _clear();
        buffer = tmp_buffer;
        buf_size *= 2;
        w_index = w_index - r_index;
        r_index = 0;
    }

private:
    char *buffer = nullptr;
    size_t w_index = 0;
    size_t r_index = 0;

    size_t buf_size = 0;
    size_t org_size = 0;
};

}

#endif //UV_CPP_BUFFER_HPP

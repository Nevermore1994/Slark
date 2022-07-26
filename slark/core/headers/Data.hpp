//
// Created by Nevermore on 2022/5/12.
// slark Data
// Copyright (c) 2022 Nevermore All rights reserved.
//
#pragma once

#include <cstdint>
#include <memory>
#include <algorithm>

namespace slark{

struct Data{
    uint64_t capacity = 0;
    uint64_t length = 0;
    char* data = nullptr;
    
    Data()
        :capacity(0)
        ,length(0)
        ,data(nullptr){
        
    }
    
    Data(const char* d, uint64_t size)
        :capacity(size)
        ,length(size)
        ,data(nullptr){
        data = new char[length];
        std::copy(d, d + size + 1, data);
    }
    
    Data(uint64_t size)
        :capacity(size)
        ,length(0)
        ,data(nullptr){
        data = new char[size];
        std::fill_n(data, size, 0);
    }
    
    ~Data(){
        release();
    }
    
    [[nodiscard]] inline Data copy() const noexcept{
        return copy(0, length);
    }
    
    [[nodiscard]] inline Data copy(uint64_t pos, uint64_t len) const noexcept {
        Data res;
        if(empty() || len == 0 || (len + pos - 1) > length){
            return res;
        }
        res.capacity = len;
        res.length = len;
        res.data = new char[len];
        std::copy(data + pos, data + pos + len, res.data);
        return res;
    }
    
    [[nodiscard]] inline std::unique_ptr<Data> copyPtr(uint64_t pos, uint64_t len) const noexcept {
        auto res = std::make_unique<Data>();
        if(empty() || len == 0 || (len + pos) > length){
            return res;
        }
        res->capacity = len;
        res->length = len;
        res->data = new char[len];
        std::copy(data + pos, data + pos + len, res->data);
        return res;
    }
    
    inline void release() noexcept{
        if(data){
            delete [] data;
            data = nullptr;
        }
        length = 0;
        capacity = 0;
    }
    
    inline void reset() const noexcept{
        if(data) {
            std::fill_n(data, length, 0);
        }
    }
    
    inline void append(const Data& d) noexcept {
        auto expectLength = length + d.length;
        if(capacity < expectLength){
            auto p = data;
            auto len = static_cast<int64_t>(expectLength * 1.5f);
            data = new char [len]; //throw except
            capacity = len;
            if(p) {
                std::copy(p, p + length, data);
                delete[] p;
            }
        }
        std::copy(d.data, d.data + d.length, data + length);
        length = expectLength;
    }
    
    inline bool empty() const noexcept{
        return length == 0;
    }
};

}

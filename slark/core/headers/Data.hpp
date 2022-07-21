//
// Created by Nevermore on 2022/5/12.
// slark Data
// Copyright (c) 2022 Nevermore All rights reserved.
//
#pragma once

#include <cstdint>
#include <memory>

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
    
    [[nodiscard]] inline Data copy(uint32_t pos, uint32_t len) const noexcept {
        Data res;
        if(empty()){
            return res;
        }
        res.capacity = len;
        res.length = len;
        res.data = new char[len];
        std::copy(data + pos, data + len + 1, res.data);
        return res;
    }
    
    [[nodiscard]] inline std::unique_ptr<Data> copy()
    
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
            data = new char [expectLength]; //throw except
            if(p){
                std::copy(data, data + length + 1, p);
                capacity = expectLength;
                delete[] p;
            }
        }
        std::copy(data + length + 1, data + expectLength + 1, d.data);
        length = expectLength;
    }
    
    inline bool empty() const noexcept{
        return length == 0;
    }
};

}
//
// Created by Nevermore on 2022/5/17.
// slark BaseClass
// Copyright (c) 2022 Nevermore All rights reserved.
//

#pragma once

#include <string>
#include <memory>
#include "Reflection.hpp"

namespace slark{

#define GetClassName(name) #name

#define HAS_MEMBER(XXX) \
template<typename T, typename... Args>\
struct has_member_##XXX \
{ \
private:  \
  template<typename U> static auto Check(int) -> decltype(std::declval<U>().XXX(std::declval<Args>()...), std::true_type());  \
  template<typename U> static std::false_type Check(...); \
public: \
  static constexpr auto value = decltype(Check<T>(0))::value; \
}

HAS_MEMBER(name);

template<typename T>
struct BaseClass{
    inline static std::string registerClass(){
        slark::RegisterClass(T);
        return GetClassName(T);
    }
    
    inline static T* create(std::string name) noexcept{
        return (T*)slark::GenerateClass(name);
    }
};


}

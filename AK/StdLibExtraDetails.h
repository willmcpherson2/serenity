/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Ali Mohammad Pur <ali.mpfard@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

namespace AK::Detail {

template<bool B, class T = void>
struct EnableIf {
};

template<class T>
struct EnableIf<true, T> {
    using Type = T;
};

template<class T, T v>
struct IntegralConstant {
    static constexpr T value = v;
    using ValueType = T;
    using Type = IntegralConstant;
    constexpr operator ValueType() const { return value; }
    constexpr ValueType operator()() const { return value; }
};

using FalseType = IntegralConstant<bool, false>;
using TrueType = IntegralConstant<bool, true>;

template<class T>
using AddConst = const T;

template<class T>
struct __RemoveConst {
    using Type = T;
};
template<class T>
struct __RemoveConst<const T> {
    using Type = T;
};
template<class T>
using RemoveConst = typename __RemoveConst<T>::Type;

template<class T>
struct __RemoveVolatile {
    using Type = T;
};

template<class T>
struct __RemoveVolatile<volatile T> {
    using Type = T;
};

template<typename T>
using RemoveVolatile = typename __RemoveVolatile<T>::Type;

template<class T>
using RemoveCV = RemoveVolatile<RemoveConst<T>>;

template<typename...>
using VoidType = void;

template<class T>
inline constexpr bool IsLvalueReference = false;

template<class T>
inline constexpr bool IsLvalueReference<T&> = true;

template<class T>
inline constexpr bool __IsPointerHelper = false;

template<class T>
inline constexpr bool __IsPointerHelper<T*> = true;

template<class T>
inline constexpr bool IsPointer = __IsPointerHelper<RemoveCV<T>>;

template<class>
inline constexpr bool IsFunction = false;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...)> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...)> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) volatile> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) volatile> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const volatile> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const volatile> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...)&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...)&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) volatile&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) volatile&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const volatile&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const volatile&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) &&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) &&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const&&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const&&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) volatile&&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) volatile&&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args...) const volatile&&> = true;
template<class Ret, class... Args>
inline constexpr bool IsFunction<Ret(Args..., ...) const volatile&&> = true;

template<class T>
inline constexpr bool IsRvalueReference = false;
template<class T>
inline constexpr bool IsRvalueReference<T&&> = true;

template<class T>
struct __RemovePointer {
    using Type = T;
};
template<class T>
struct __RemovePointer<T*> {
    using Type = T;
};
template<class T>
struct __RemovePointer<T* const> {
    using Type = T;
};
template<class T>
struct __RemovePointer<T* volatile> {
    using Type = T;
};
template<class T>
struct __RemovePointer<T* const volatile> {
    using Type = T;
};
template<typename T>
using RemovePointer = typename __RemovePointer<T>::Type;

template<typename T, typename U>
inline constexpr bool IsSame = false;

template<typename T>
inline constexpr bool IsSame<T, T> = true;

template<bool condition, class TrueType, class FalseType>
struct __Conditional {
    using Type = TrueType;
};

template<class TrueType, class FalseType>
struct __Conditional<false, TrueType, FalseType> {
    using Type = FalseType;
};

template<bool condition, class TrueType, class FalseType>
using Conditional = typename __Conditional<condition, TrueType, FalseType>::Type;

template<typename T>
inline constexpr bool IsNullPointer = IsSame<decltype(nullptr), RemoveCV<T>>;

template<typename T>
struct __RemoveReference {
    using Type = T;
};
template<class T>
struct __RemoveReference<T&> {
    using Type = T;
};
template<class T>
struct __RemoveReference<T&&> {
    using Type = T;
};

template<typename T>
using RemoveReference = typename __RemoveReference<T>::Type;

template<typename T>
struct __MakeUnsigned {
    using Type = void;
};
template<>
struct __MakeUnsigned<signed char> {
    using Type = unsigned char;
};
template<>
struct __MakeUnsigned<short> {
    using Type = unsigned short;
};
template<>
struct __MakeUnsigned<int> {
    using Type = unsigned int;
};
template<>
struct __MakeUnsigned<long> {
    using Type = unsigned long;
};
template<>
struct __MakeUnsigned<long long> {
    using Type = unsigned long long;
};
template<>
struct __MakeUnsigned<unsigned char> {
    using Type = unsigned char;
};
template<>
struct __MakeUnsigned<unsigned short> {
    using Type = unsigned short;
};
template<>
struct __MakeUnsigned<unsigned int> {
    using Type = unsigned int;
};
template<>
struct __MakeUnsigned<unsigned long> {
    using Type = unsigned long;
};
template<>
struct __MakeUnsigned<unsigned long long> {
    using Type = unsigned long long;
};
template<>
struct __MakeUnsigned<char> {
    using Type = unsigned char;
};
template<>
struct __MakeUnsigned<char8_t> {
    using Type = char8_t;
};
template<>
struct __MakeUnsigned<char16_t> {
    using Type = char16_t;
};
template<>
struct __MakeUnsigned<char32_t> {
    using Type = char32_t;
};
template<>
struct __MakeUnsigned<bool> {
    using Type = bool;
};

template<typename T>
using MakeUnsigned = typename __MakeUnsigned<T>::Type;

template<typename T>
struct __MakeSigned {
};
template<>
struct __MakeSigned<signed char> {
    using Type = signed char;
};
template<>
struct __MakeSigned<short> {
    using Type = short;
};
template<>
struct __MakeSigned<int> {
    using Type = int;
};
template<>
struct __MakeSigned<long> {
    using Type = long;
};
template<>
struct __MakeSigned<long long> {
    using Type = long long;
};
template<>
struct __MakeSigned<unsigned char> {
    using Type = char;
};
template<>
struct __MakeSigned<unsigned short> {
    using Type = short;
};
template<>
struct __MakeSigned<unsigned int> {
    using Type = int;
};
template<>
struct __MakeSigned<unsigned long> {
    using Type = long;
};
template<>
struct __MakeSigned<unsigned long long> {
    using Type = long long;
};
template<>
struct __MakeSigned<char> {
    using Type = char;
};

template<typename T>
using MakeSigned = typename __MakeSigned<T>::Type;

template<class T>
inline constexpr bool IsVoid = IsSame<void, RemoveCV<T>>;

template<class T>
inline constexpr bool IsConst = false;

template<class T>
inline constexpr bool IsConst<const T> = true;

template<typename T>
inline constexpr bool IsEnum = __is_enum(T);

template<typename T>
inline constexpr bool IsUnion = __is_union(T);

template<typename T>
inline constexpr bool IsClass = __is_class(T);

template<typename Base, typename Derived>
inline constexpr bool IsBaseOf = __is_base_of(Base, Derived);

template<typename T>
inline constexpr bool __IsIntegral = false;

template<>
inline constexpr bool __IsIntegral<bool> = true;
template<>
inline constexpr bool __IsIntegral<unsigned char> = true;
template<>
inline constexpr bool __IsIntegral<char8_t> = true;
template<>
inline constexpr bool __IsIntegral<char16_t> = true;
template<>
inline constexpr bool __IsIntegral<char32_t> = true;
template<>
inline constexpr bool __IsIntegral<unsigned short> = true;
template<>
inline constexpr bool __IsIntegral<unsigned int> = true;
template<>
inline constexpr bool __IsIntegral<unsigned long> = true;
template<>
inline constexpr bool __IsIntegral<unsigned long long> = true;

template<typename T>
inline constexpr bool IsIntegral = __IsIntegral<MakeUnsigned<RemoveCV<T>>>;

template<typename T>
inline constexpr bool __IsFloatingPoint = false;
template<>
inline constexpr bool __IsFloatingPoint<float> = true;
template<>
inline constexpr bool __IsFloatingPoint<double> = true;
template<>
inline constexpr bool __IsFloatingPoint<long double> = true;

template<typename T>
inline constexpr bool IsFloatingPoint = __IsFloatingPoint<RemoveCV<T>>;

template<typename ReferenceType, typename T>
using CopyConst = Conditional<IsConst<ReferenceType>, AddConst<T>, RemoveConst<T>>;

template<typename... Ts>
using Void = void;

template<typename... _Ignored>
constexpr auto DependentFalse = false;

template<typename T>
inline constexpr bool IsSigned = IsSame<T, MakeSigned<T>>;

template<typename T>
inline constexpr bool IsUnsigned = IsSame<T, MakeUnsigned<T>>;

template<typename T>
inline constexpr bool IsArithmetic = IsIntegral<T> || IsFloatingPoint<T>;

template<typename T>
inline constexpr bool IsFundamental = IsArithmetic<T> || IsVoid<T> || IsNullPointer<T>;

template<typename T, T... Ts>
struct IntegerSequence {
    using Type = T;
    static constexpr unsigned size() noexcept { return sizeof...(Ts); };
};

template<unsigned... Indices>
using IndexSequence = IntegerSequence<unsigned, Indices...>;

template<typename T, T N, T... Ts>
auto make_integer_sequence_impl()
{
    if constexpr (N == 0)
        return IntegerSequence<T, Ts...> {};
    else
        return make_integer_sequence_impl<T, N - 1, N - 1, Ts...>();
}

template<typename T, T N>
using MakeIntegerSequence = decltype(make_integer_sequence_impl<T, N>());

template<unsigned N>
using MakeIndexSequence = MakeIntegerSequence<unsigned, N>;

template<typename T>
struct __IdentityType {
    using Type = T;
};

template<typename T>
using IdentityType = typename __IdentityType<T>::Type;

template<class T>
requires(IsEnum<T>) using UnderlyingType = __underlying_type(T);

template<typename T>
inline constexpr bool IsTrivial = __is_trivial(T);

template<typename T>
inline constexpr bool IsTriviallyCopyable = __is_trivially_copyable(T);

}
using AK::Detail::AddConst;
using AK::Detail::Conditional;
using AK::Detail::CopyConst;
using AK::Detail::DependentFalse;
using AK::Detail::EnableIf;
using AK::Detail::FalseType;
using AK::Detail::IdentityType;
using AK::Detail::IndexSequence;
using AK::Detail::IntegerSequence;
using AK::Detail::IsArithmetic;
using AK::Detail::IsBaseOf;
using AK::Detail::IsClass;
using AK::Detail::IsConst;
using AK::Detail::IsEnum;
using AK::Detail::IsFloatingPoint;
using AK::Detail::IsFunction;
using AK::Detail::IsFundamental;
using AK::Detail::IsIntegral;
using AK::Detail::IsLvalueReference;
using AK::Detail::IsNullPointer;
using AK::Detail::IsPointer;
using AK::Detail::IsRvalueReference;
using AK::Detail::IsSame;
using AK::Detail::IsSigned;
using AK::Detail::IsTrivial;
using AK::Detail::IsTriviallyCopyable;
using AK::Detail::IsUnion;
using AK::Detail::IsUnsigned;
using AK::Detail::IsVoid;
using AK::Detail::MakeIndexSequence;
using AK::Detail::MakeIntegerSequence;
using AK::Detail::MakeSigned;
using AK::Detail::MakeUnsigned;
using AK::Detail::RemoveConst;
using AK::Detail::RemoveCV;
using AK::Detail::RemovePointer;
using AK::Detail::RemoveReference;
using AK::Detail::RemoveVolatile;
using AK::Detail::TrueType;
using AK::Detail::UnderlyingType;
using AK::Detail::Void;
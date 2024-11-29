#ifndef MULT_HPP_
#define MULT_HPP_

#include <array>
#include <cassert>
#include <type_traits>
#include <tuple>
#include <utility>
#include <iostream>
#include <string>

namespace custom {

template <int M, int K, int S>
struct Unit {
    enum { m = M, kg = K, s = S };
};

using M    = Unit<1, 0, 0>;   // meter
using Kg   = Unit<0, 1, 0>;   // kilogram
using S    = Unit<0, 0, 1>;   // second
using MpS  = Unit<1, 0, -1>;  // meter per second = velocity
using MpS2 = Unit<1, 0, -2>;  // meter per second squared = acceleration

template <typename U1, typename U2>
struct Uplus {
    using type = Unit<U1::m + U2::m, U1::kg + U2::kg , U1::s + U2::s>;
};

template <typename U1, typename U2>
using Unit_plus = typename Uplus<U1, U2>::type;

template <typename U1, typename U2>
struct Uminus {
    using type = Unit<U1::m - U2::m, U1::kg - U2::kg, U1::s - U2::s>;
};

template <typename U1, typename U2>
using Unit_minus = typename Uminus<U1, U2>::type;

template <typename U>
using Unit_negate = typename Uminus<Unit<0, 0, 0>, U>::type;

template <typename U, typename V = double>
struct Value {
    V val;
    explicit constexpr Value(V d) : val {d} {}

    template <typename V2>
    constexpr Value(Value<U, V2> d) : val {static_cast<V>(d.val)} {}
};

template <typename U1, typename U2, typename V1, typename V2>
auto operator*(Value<U1, V1> x, Value<U2, V2> y) {
    return Value<Unit_plus<U1, U2>, decltype(x.val * y.val)>(x.val * y.val);
}

template <typename U1, typename U2, typename V1, typename V2>
auto operator/(Value<U1, V1> x, Value<U2, V2> y) {
    return Value<Unit_minus<U1, U2>, decltype(x.val / y.val)>(x.val / y.val);
}

constexpr Value<M, long double> operator"" _m(long double value) {
    return Value<M, long double>{value};
}

constexpr Value<Kg, long double> operator"" _kg(long double value) {
    return Value<Kg, long double>{value};
}

constexpr Value<S, long double> operator"" _s(long double value) {
    return Value<S, long double>{value};
}

template <typename U, typename V>
bool operator==(Value<U, V> x, Value<U, V> y) {
    return x.val == y.val;
}

} // namespace custom

#endif // MULT_HPP_

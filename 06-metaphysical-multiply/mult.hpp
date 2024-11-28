#ifndef MULT_HPP_
#define MULT_HPP_

#include <tuple>
#include <utility>
#include <type_traits>
#include <array>

template<int... Ints>
struct Unit : std::integer_sequence<int, Ints...> {
    using type = std::integer_sequence<int, Ints...>;
    static constexpr std::array<int, sizeof...(Ints)> values() {
        return {Ints...};
    }
};

namespace std {
    template<int... Ints>
    struct tuple_size<Unit<Ints...>> : std::integral_constant<std::size_t, sizeof...(Ints)> {};

    template<std::size_t Index, int... Ints>
    struct tuple_element<Index, Unit<Ints...>> {
        using type = int;
    };

    template<std::size_t Index, int... Ints>
    constexpr int get(const Unit<Ints...>&) {
        return Unit<Ints...>::values()[Index];
    }
}

template <typename Unit>
struct Value {
    double val;
    explicit constexpr Value(double d) : val(d) {}
    explicit constexpr operator double() const { return val; }
    template <typename Other>
    explicit constexpr Value(Value<Other> other) : val(other.val) {
        static_assert(Unit{} == Other{}, "Dimensions incompatible");
    }
};

template <typename Tuple1, typename Tuple2, std::size_t... Indices>
constexpr auto zip_with_add_impl(std::index_sequence<Indices...>) {
    return Unit<(std::get<Indices>(Tuple1{}) + std::get<Indices>(Tuple2{}))...>{};
}

template <typename Tuple1, typename Tuple2>
constexpr auto zip_with_add(const Tuple1&, const Tuple2&) {
    static_assert(std::tuple_size_v<Tuple1> == std::tuple_size_v<Tuple2>, "Tuples must have the same size");
    return zip_with_add_impl<Tuple1, Tuple2>(std::make_index_sequence<std::tuple_size_v<Tuple1>>{});
}

template <typename Tuple1, typename Tuple2, std::size_t... Indices>
constexpr auto zip_with_sub_impl(std::index_sequence<Indices...>) {
    return Unit<(std::get<Indices>(Tuple1{}) - std::get<Indices>(Tuple2{}))...>{};
}

template <typename Tuple1, typename Tuple2>
constexpr auto zip_with_sub(const Tuple1&, const Tuple2&) {
    static_assert(std::tuple_size_v<Tuple1> == std::tuple_size_v<Tuple2>, "Tuples must have the same size");
    return zip_with_sub_impl<Tuple1, Tuple2>(std::make_index_sequence<std::tuple_size_v<Tuple1>>{});
}

template <typename D1, typename D2>
constexpr auto operator*(Value<D1> a, Value<D2> b) {
    using D = decltype(zip_with_add(D1{}, D2{}));
    return Value<D>{double(a) * double(b)};
}

template <typename D1, typename D2>
constexpr auto operator/(Value<D1> a, Value<D2> b) {
    using D = decltype(zip_with_sub(D1{}, D2{}));
    return Value<D>{double(a) / double(b)};
}

using Meter = Unit<1, 0, 0>;
using Meter2 = Unit<2, 0, 0>;
using Second = Unit<0, 0, 1>;
using Second2 = Unit<0, 0, 2>;
using Scalar = Value<Unit<0, 0, 0>>;
using Length = Value<Unit<1, 0, 0>>;
using Speed = Value<Unit<1, 0, -1>>;
using Acceleration = Value<Unit<1, 0, -2>>;

constexpr Value<Meter> operator"" _m(long double d) { return Value<Meter>(d); }
constexpr Value<Meter2> operator"" _m2(long double d) { return Value<Meter2>(d); }
constexpr Value<Second> operator"" _s(long double d) { return Value<Second>(d); }
constexpr Value<Second2> operator"" _s2(long double d) { return Value<Second2>(d); }

#endif // MULT_HPP_

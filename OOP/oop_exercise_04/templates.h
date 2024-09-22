#ifndef D_TEMPLATES_H_
#define D_TEMPLATES_H_ 1

#include <tuple>
#include <type_traits>

#include "square.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "vertex.h"

template<class T>
struct is_vertex : std::false_type {};

template<class T>
struct is_vertex<vertex<T>> : std::true_type {};

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...>> :
    std::conjunction<is_vertex<Head>,
      std::is_same<Head, Tail>...> {};

template<class Type, size_t SIZE>
struct is_figurelike_tuple<std::array<Type, SIZE>> :
    is_vertex<Type> {};

template<class T>
inline constexpr bool is_figurelike_tuple_v =
  is_figurelike_tuple<T>::value;

template<class T, class = void>
struct has_print_method : std::false_type {};

template<class T>
struct has_print_method<T,
  std::void_t<decltype(std::declval<const T>().Print())>> :
    std::true_type {};

template<class T>
inline constexpr bool has_print_method_v =
  has_print_method<T>::value;

template<class T>
std::enable_if_t<has_print_method_v<T>, void>
    Print(const T& figure) {
        figure.Print();
}

template<size_t ID, class T>
void single_print(const T& t) {
    std::cout << std::get<ID>(t);
    return ;
}

template<size_t ID, class T>
void RecursivePrint(const T& t) {
    if constexpr (ID < std::tuple_size_v<T>){
        single_print<ID>(t);
        RecursivePrint<ID+1>(t);
        return ;
    }
    return;
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
    Print(const T& fake) {
    return RecursivePrint<0>(fake);
}

template<class T, class = void>
struct has_center_method : std::false_type {};

template<class T>
struct has_center_method<T,
        std::void_t<decltype(std::declval<const T>().Center())>> :
        std::true_type {};

template<class T>
inline constexpr bool has_center_method_v =
        has_center_method<T>::value;

template<class T>
std::enable_if_t<has_center_method_v<T>, vertex<double>>
Center(const T& figure) {
    return figure.Center();
}

template<class T>
inline constexpr const int tuple_size_v = std::tuple_size<T>::value;

template<size_t ID, class T>
vertex<double> single_center(const T& t) {
    vertex<double> v;
    v.x = std::get<ID>(t).x;
    v.y = std::get<ID>(t).y;
    v /= std::tuple_size_v<T>;
    return v;
}

template<size_t ID, class T>
vertex<double> RecursiveCenter(const T& t) {
    if constexpr (ID < std::tuple_size_v<T>){
        return  single_center<ID>(t) + RecursiveCenter<ID+1>(t);
    } else {
        vertex<double> v;
        v.x = 0;
        v.y = 0;
        return v;
    }
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, vertex<double>>
Center(const T& fake) {
    return RecursiveCenter<0>(fake);
}

template<class T, class = void>
struct has_area_method : std::false_type {};

template<class T>
struct has_area_method<T,
        std::void_t<decltype(std::declval<const T>().Area())>> :
        std::true_type {};

template<class T>
inline constexpr bool has_area_method_v =
        has_area_method<T>::value;

template<class T>
std::enable_if_t<has_area_method_v<T>, double>
Area(const T& figure) {
    return figure.Area();
}

template<size_t ID, class T>
double single_area(const T& t) {
    const auto& a = std::get<0>(t);
    const auto& b = std::get<ID - 1>(t);
    const auto& c = std::get<ID>(t);
    const double dx1 = b.x - a.x;
    const double dy1 = b.y - a.y;
    const double dx2 = c.x - a.x;
    const double dy2 = c.y - a.y;
    return std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
}

template<size_t ID, class T>
double RecursiveArea(const T& t) {
    if constexpr (ID < std::tuple_size_v<T>){
        return single_area<ID>(t) + RecursiveArea<ID + 1>(t);
    }
    return 0;
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, double>
Area(const T& fake) {
    return RecursiveArea<2>(fake);
}

#endif // D_TEMPLATES_H_

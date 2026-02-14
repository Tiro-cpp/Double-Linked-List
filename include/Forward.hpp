#pragma once
#include <type_traits>

template<typename T>
T&& forward(std::remove_reference_t<T>& arg) {
 return static_cast<T&&>(arg);
}

template<typename T>
T&& forward(std::remove_reference_t<T>&& arg) {
return static_cast<T&&>(arg);
}

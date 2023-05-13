#pragma once

#include <system_error>
#include <iostream>
#include <string_view>
#include <Windows.h>

// https://artificial-mind.net/blog/2020/09/26/dont-deduce
// a "hack" to prevent the compiler from deducing template arguments
template<typename T>
using dont_deduce = typename std::common_type<T>::type;

std::system_error system_error_from_win32(std::string_view error_msg) {
    auto error = GetLastError();
    std::error_code ec((int)error, std::system_category());
    return {ec, error_msg.data()};
}

template<typename T>
static inline T check_error(const std::string& fn, dont_deduce<T> error_sentinel, T return_value) {
    if (return_value == error_sentinel) {
        throw system_error_from_win32(fn);
    }
    return return_value;
}

#define CHECK_ERROR(fn) check_error(#fn, nullptr, fn)
#define CHECK_ERROR_V(V, fn) check_error(#fn, V, fn)

template<typename Thunk>
void error_to_panic(Thunk thunk) {
    try {
        thunk();
    } catch (std::exception& e) {
        std::wcerr << e.what() << L"\n";
        exit(1);
    } catch (...) {
        std::wcerr << L"Unknown error\n";
        exit(1);
    }
}

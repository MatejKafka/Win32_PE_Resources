#include <iostream>
#include <Windows.h>
#include <string>
#include <optional>
#include "../lib/util.hpp"

// string IDs go to `2^16 * 16`, each stringtable contains 16 strings
std::optional<std::wstring_view> load_string_resource(size_t string_id) {
    wchar_t* resource = nullptr;
    int string_size = LoadString(GetModuleHandle(nullptr), string_id, (wchar_t*)&resource, 0);
    if (string_size < 0) {
        throw system_error_from_win32("Could not load string");
    }

    if (string_size == 0) {
        return std::nullopt;
    } else {
        return std::wstring_view{resource, (size_t)string_size};
    }
}

int main() {
    error_to_panic([&] {
        for (auto i : {1, 17}) {
            auto str = load_string_resource(i);
            if (!str) {
                throw std::runtime_error("String " + std::to_string(i) + " does not exist\n");
            }
            wprintf(L"String #%d: ", i);
            fwrite(str->data(), sizeof(wchar_t), str->size(), stdout);
            wprintf(L"\n");
        }
    });
}

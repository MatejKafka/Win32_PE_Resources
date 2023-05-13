#include <Windows.h>
#include <iostream>
#include <vector>
#include <cassert>
#include "../lib/util.hpp"
#include "../lib/resource_lib.hpp"

/**
 * Builds a stringtable resource, where `string_i`-th string is set to `string`
 * and all other strings are empty. `string_i` must be less than 16.
 */
std::vector<wchar_t> build_stringtable(size_t string_i, std::wstring_view string) {
    assert(string_i < 16);

    // https://www.codeproject.com/Articles/8340/Using-UpdateResource-to-change-a-string-resource
    auto resource_size_wchar = string_i + 1 + string.size();
    if (resource_size_wchar % 2 != 0) resource_size_wchar++;

    std::vector<wchar_t> resource_buffer(resource_size_wchar);

    for (size_t i = 0; i < string_i; i++) {
        resource_buffer[i] = 0;
    }
    resource_buffer[string_i] = string.size();
    std::memcpy(&resource_buffer[string_i + 1], string.data(), string.size() * sizeof(wchar_t));

    return resource_buffer;
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        std::wcerr << L"Expected exactly 1 argument\n";
        return 2;
    }

    error_to_panic([&] {
        PeResources::ResourceUpdater updater{argv[1]};

        auto resource_buffer = build_stringtable(1, L"Hello there");
        wprintf(L"Writing string resources at #1 and #17...\n");
        updater.update_resource(RT_STRING, 1, std::span(resource_buffer));
        // this creates string with ID 17 (first string in second 16 string block)
        updater.update_resource(RT_STRING, 2, std::span(resource_buffer));

        std::wstring rcdata_resource = L"hello";
        wprintf(L"Writing RCDATA resource with ID 1...\n");
        updater.update_resource(RT_RCDATA, 1, std::span(rcdata_resource));
        wprintf(L"Writing RCDATA resource called 'Name'...\n");
        updater.update_resource(RT_RCDATA, L"Name", std::span(rcdata_resource));

        updater.commit();
    });
}
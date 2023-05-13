#include <string>
#include "../lib/resource_lib.hpp"

std::wstring atom_to_string(LPCWSTR atom) {
    if ((uintptr_t)atom > 0xffff) {
        return std::wstring(L"NAME=") + atom;
    } else {
        return L"ID#" + std::to_wstring((uint16_t)(uintptr_t)atom);
    }
}

std::wstring resource_type_to_string(PeResources::RType resource_type) {
    if (resource_type == RT_CURSOR) return L"CURSOR";
    if (resource_type == RT_BITMAP) return L"BITMAP";
    if (resource_type == RT_ICON) return L"ICON";
    if (resource_type == RT_MENU) return L"MENU";
    if (resource_type == RT_DIALOG) return L"DIALOG";
    if (resource_type == RT_STRING) return L"STRING";
    if (resource_type == RT_FONTDIR) return L"FONTDIR";
    if (resource_type == RT_FONT) return L"FONT";
    if (resource_type == RT_ACCELERATOR) return L"ACCELERATOR";
    if (resource_type == RT_RCDATA) return L"RCDATA";
    if (resource_type == RT_MESSAGETABLE) return L"MESSAGETABLE";
    if (resource_type == RT_GROUP_CURSOR) return L"GROUP_CURSOR";
    if (resource_type == RT_GROUP_ICON) return L"GROUP_ICON";
    if (resource_type == RT_VERSION) return L"VERSION";
    if (resource_type == RT_DLGINCLUDE) return L"DLGINCLUDE";
    if (resource_type == RT_PLUGPLAY) return L"PLUGPLAY";
    if (resource_type == RT_VXD) return L"VXD";
    if (resource_type == RT_ANICURSOR) return L"ANICURSOR";
    if (resource_type == RT_ANIICON) return L"ANIICON";
    if (resource_type == RT_HTML) return L"HTML";
    if (resource_type == RT_MANIFEST) return L"MANIFEST";
    // unknown resource type
    return atom_to_string(resource_type);
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        std::wcerr << L"Expected 1 argument\n";
        return 2;
    }

    error_to_panic([&] {
        PeResources::LibraryModule m{argv[1]};

        m.enumerate_resource_types([&](auto type) {
            auto type_str = resource_type_to_string(type);
            m.enumerate_resources(type, [&](auto name) {
                wprintf(L"Found resource, type %s, %s\n",
                        type_str.c_str(), atom_to_string(name).c_str());
            });
        });
    });
}
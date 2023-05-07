#include <iostream>
#include <Windows.h>
#include "../lib/util.hpp"
#include "../lib/resource_lib.hpp"


int wmain(int argc, wchar_t* argv[]) {
    if (argc != 3) {
        std::wcerr << L"Expected exactly 2 arguments\n";
        return 2;
    }

    error_to_panic([&] {
        PeResources::LibraryModule src_module{argv[1]};
        PeResources::ResourceUpdater updater{argv[2]};

        auto copy_resource_type = [&](auto type) {
            src_module.enumerate_resources(type, [&](auto name) {
                updater.update_resource(type, name, src_module.load_resource(type, name));
            });
        };

        // copy all icons and icon groups
        copy_resource_type(RT_ICON);
        copy_resource_type(RT_GROUP_ICON);
        // copy version info
        copy_resource_type(RT_VERSION);

        updater.commit();
    });
}
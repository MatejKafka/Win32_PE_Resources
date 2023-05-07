# Win32 PE Resource editing

A set of examples and a small C++20 library to illustrate copying and updating resources embedded in PE (.exe/.dll) files using Win32 APIs.

## Usage

See the examples in the `/examples/` subdirectory and the source code of the library in `/lib/`.

```cpp
PeResources::LibraryModule src_module{src_path};
PeResources::ResourceUpdater updater{destination_path};

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

// apply the update
updater.commit();
```
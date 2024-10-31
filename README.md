# Block Craft 3D

This is my attempt at a Voxel engine in C++ with modern OpenGL.

## Building

This project uses CMake and CMake's `FetchContent` to automatically download dependencies.

```bash
git clone https://www.github.com/NaniNoni/Block-Craft-3D
cd Block-Craft-3D
mkdir build
cd build
cmake .. -G Ninja # Ninja is the recommended build tool, but others should work
cmake --build .
```

## Running

Just run the executable in the build directory. All dependencies are statically linked.

## Bugs

Right now, this is very much a work in progress. Please only report crashes.

## Attribution

The textures are by [PiiiXL](https://piiixl.itch.io/) and are licenced under
[CC BY 4.0](https://creativecommons.org/licenses/by/4.0/deed.en#ref-appropriate-credit)
without any changes.

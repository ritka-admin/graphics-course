![build_cmake_status](https://github.com/sadads1337/mse-gl-hw-template/actions/workflows/build_cmake.yml/badge.svg)

# Mandelbrot fractal

Mandelbrot set representation with zooming, navigation and parameters changing.

<img src="https://github.com/ritka-admin/morphing-plus-phong-shading/assets/100676145/8bd68acc-29c9-4ddb-af22-1dcfb4ec4ad4" alt="drawing" width="500"/>

## Requirements

- git [https://git-scm.com](https://git-scm.com);
- C++17 compatible compiler;
- CMake 3.10+ [https://cmake.org/](https://cmake.org/);
- Qt 5 [https://www.qt.io/](https://www.qt.io/);
- (Optionally) Your favourite IDE;
- (Optionally) Ninja build [https://ninja-build.org/](https://ninja-build.org/).

## Hardware requirements

- GPU with OpenGL 3+ support.

## Build from console

- Clone this repository `git clone <url> <path>`;
- Go to root folder `cd <path-to-repo-root>`;
- Create and go to build folder `mkdir -p build-release; cd build-release`;
- Run CMake `cmake .. -G <generator-name> -DCMAKE_PREFIX_PATH=<path-to-qt-installation> -DCMAKE_BUILD_TYPE=Release`;
- Run build. For Ninja generator it looks like `ninja -j<number-of-threads-to-build>`.

## Build with MSVC

- Clone this repository `git clone <url> <path>`;
- Open root folder in IDE;
- Build, possibly specify build configurations and path to Qt library.

## Run and debug

- Since we link with Qt dynamically don't forget to add `<qt-path>/<abi-arch>/bin` and `<qt-path>/<abi-arch>/plugins/platforms` to `PATH` variable.

# VSTExample

Example Steinberg VST3 plugin based on the Sloe Compurters PDK.

## Status

Build failing as VST_SDK has not been made available..

[![Build Status](https://github.com/SloeComputers/VSTExample/actions/workflows/build_on_push.yml/badge.svg)](https://github.com/SloeComputers/VSTExample/actions/workflows/build_on_push.yml)

Being developed on MacOS. Will explore Linux builds once more progress has been made.

## Checkout

This repo uses git sub-modules, so checkout using --recurse to clone all the
dependent source...

    git clone --recurse https://github.com/SloeComputers/VSTExample.git

or

    git clone --recurse ssh://git@github.com/SloeComputers/VSTExample.git

## Dependencies

+ https://github.com/SloeComputers/PDK
+ cmake via UNIX make or auto detection of ninja if installed
+ Python3
+ VST_SDK - currently using vst-sdk_3.8.0_build-66_2025-10-20.zip

## Build

The environment variable `VST_SDK` needs to be made available and point at an install of the VST3 SDK source.

Indirect build with cmake and make (or ninja)...

```
make
```

Build the vst3 target...

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DPDK_TARGET=vst3
make
```

The built `.vst3` bundle will be under the CMake build output directory.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

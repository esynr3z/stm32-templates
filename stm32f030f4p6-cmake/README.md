## CMake project template for STM32F030F4P6

### Features

* STM32F0xx SPL v1.5.0 used
* PLL 48MHz from internal HSI 8MHz
* Led blinking on PA4
* Only for out-of-source build
* Cross platform - Windows compatible
* CMake 3.8 minimum required

### Build

Debug build - no optimization (-0g) and debug information included (-g):
```bash
#From project root (stm32f030f4p6 dir)
mkdir build-debug && cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ../src
cmake --build .
```

Release build - size optimizations (-0s), link-time optimization (-flto):
```bash
#From project root (stm32f030f4p6 dir)
mkdir build-release && cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ../src
cmake --build .
```

Clean:
```bash
#Simply remove build dirs from project root
rm -rf build-release build-debug
```

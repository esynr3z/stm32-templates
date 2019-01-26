## CMake project template for STM32F103C8T6

### Features

* Tested on STM32 Blue Pill
* STM32F1xx HAL Driver V1.1.2 (used only LL part)
* PLL 72MHz from HSE 8MHz
* Led blinking on PC13 from TIM2 update irq
* Printf() string to USART1 at PA9 (115200, 8 data bit, 1 start bit, 1 stop bit, no parity)
* MCO with SYSCLK at PA8
* Only for out-of-source build
* Cross platform - Windows compatible
* CMake 3.8 minimum required

### Build

Debug build - no optimization (-0g) and debug information included (-g):
```bash
#From project root (stm32f103c8t6-cmake dir)
mkdir build-debug && cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

Release build - size optimizations (-0s), link-time optimization (-flto):
```bash
#From project root (stm32f103c8t6-cmake dir)
mkdir build-release && cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

Clean:
```bash
#Simply remove build dirs from project root
rm -rf build-release build-debug
```

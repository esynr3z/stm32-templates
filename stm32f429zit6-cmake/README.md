## CMake project template for STM32F429ZIT6

### Features

* Tested on STM32F429I-DISCO
* STM32F4xx HAL Driver V1.7.4 (used only LL part)
* PLL 180MHz from HSE 8MHz
* Prefetch and cache enabled
* Led blinking on PG13 from TIM2 update irq
* Printf() string to USART1 at PA9 (115200, 8 data bit, 1 start bit, 1 stop bit, no parity)
* MCO with SYSCLK/4 at PC9
* Only for out-of-source build
* Cross platform - Windows compatible
* CMake 3.8 minimum required

### Build

Debug build - no optimization (-0g) and debug information included (-g):
```bash
#From project root (stm32f429zit6-cmake dir)
mkdir build-debug && cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

Release build - size optimizations (-0s), link-time optimization (-flto):
```bash
#From project root (stm32f429zit6-cmake dir)
mkdir build-release && cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

Clean:
```bash
#Simply remove build dirs from project root
rm -rf build-release build-debug
```

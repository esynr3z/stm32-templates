## Makefile project template for STM32F030F4P6

### Features

* STM32F0xx SPL v1.5.0 used
* PLL 48MHz from internal HSI 8MHz
* Led blinking on PA4
* All build results stored in ```build``` folder
* Cross platform fixes in makefile - Windows compatible

### Build

Build project:
```
make
```

Clean project:
```
make clean
```

### Misc

Makefile can generate basic Qt Creator project from available information:
```
make qtproj
```
Note: Windows users may have problems with line endings - '\n' should be manually replaced for newlines.
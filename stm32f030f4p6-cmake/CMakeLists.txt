#-- Service --------------------------------------------------------------------
SET(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/gcc_stm32f0x.cmake)
CMAKE_MINIMUM_REQUIRED(VERSION 3.8.0)
ENABLE_LANGUAGE(ASM)
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
ENDIF()
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#-- Project name ---------------------------------------------------------------
PROJECT(template)

#-- Defines --------------------------------------------------------------------
ADD_DEFINITIONS(-DUSE_FULL_ASSERT=1)
ADD_DEFINITIONS(-DUSE_STDPERIPH_DRIVER)
ADD_DEFINITIONS(-DSTM32F030)

#-- Project paths --------------------------------------------------------------
SET(APP_PATH                app)
SET(LIBS_PATH               lib)
SET(CMSIS_DEVICE_SRC_PATH   ${LIBS_PATH}/CMSIS/Device/ST/STM32F0xx/Source/Template/GCC)
SET(CMSIS_DEVICE_INC_PATH   ${LIBS_PATH}/CMSIS/Device/ST/STM32F0xx/Include)
SET(CMSIS_CORE_INC_PATH     ${LIBS_PATH}/CMSIS/Core/Include)
SET(SPL_SRC_PATH            ${LIBS_PATH}/STM32F0xx_SPL_V1.5.0/src)
SET(SPL_INC_PATH            ${LIBS_PATH}/STM32F0xx_SPL_V1.5.0/inc)

#-- Include dirs ---------------------------------------------------------------
INCLUDE_DIRECTORIES(${APP_PATH})
INCLUDE_DIRECTORIES(${SPL_INC_PATH})
INCLUDE_DIRECTORIES(${CMSIS_CORE_INC_PATH})
INCLUDE_DIRECTORIES(${CMSIS_DEVICE_INC_PATH})

#-- Sources list ---------------------------------------------------------------
FILE(GLOB_RECURSE APP_SRC ${APP_PATH}/*.c)
LIST(APPEND APP_SRC ${CMSIS_DEVICE_SRC_PATH}/startup_stm32f030.S)

#-- Libs -----------------------------------------------------------------------
FILE(GLOB_RECURSE SPL_SRC ${SPL_SRC_PATH}/*.c)
ADD_LIBRARY(
    SPL
    ${SPL_SRC}
)

#-- Linker script --------------------------------------------------------------
SET(LDSCRIPT ${CMAKE_SOURCE_DIR}/${CMSIS_DEVICE_SRC_PATH}/STM32F030F4P6.ld)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LDSCRIPT} -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map")

#-- Project linking ------------------------------------------------------------
ADD_EXECUTABLE(${PROJECT_NAME}.elf ${APP_SRC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}.elf SPL)

#-- Custom commands ------------------------------------------------------------
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} "-Oihex" ${PROJECT_NAME}.elf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} "-Obinary" ${PROJECT_NAME}.elf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
        COMMAND ${CMAKE_OBJDUMP} "-DS" ${PROJECT_NAME}.elf > ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.dasm
        COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf)

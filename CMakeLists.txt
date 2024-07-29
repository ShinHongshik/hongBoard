cmake_minimum_required(VERSION 3.5)

# if(NOT WIN32)
	string(ASCII 27 Esc)
	# set(RESET                   "\033[0m")
	set(RESET                   "${Esc}[0m")
	set(ColourBold              "${Esc}[1m")
	set(Red                     "${Esc}[31m")
	set(Green                   "${Esc}[32m")
	set(Yellow                  "${Esc}]33m")
	set(Blue                    "${Esc}]34")
	set(Magenta                 "${Esc}]35m")
	set(Cyan                    "${Esc}]36m")
	set(White                   "${Esc}[37m")
	set(BoldRed                 "${Esc}[1;31m")
	set(BoldGreen               "${Esc}[1;32m")
	set(BoldYellow              "${Esc}[1;33m")
	set(BoldBlue                "${Esc}[1;34m")
	set(BoldMagenta             "${Esc}[1;35m")
	set(BoldCyan                "${Esc}[1;36m")
	set(BoldWhite               "${Esc}[1;37m")
# endif()

set(PRJ_NAME                HongRp2040)
set(CMAKE_C_STANDARD        11)
set(CMAKE_CXX_STANDARD      17)
set(PICO_SDK_PATH           "${CMAKE_SOURCE_DIR}/external/pico-sdk")         # set(PICO_SDK_PATH           ${PICO_SDK_PATH})
set(PICO_SDK_EXTRAS_PATH    "${CMAKE_SOURCE_DIR}/external/pico-extras")      # set(PICO_SDK_EXTRAS_PATH    ${PICO_EXTRAS_PATH})
set(WIZNET_DIR              "${CMAKE_SOURCE_DIR}/external/ioLibrary_Driver") 
# set(PICO_BOARD_HEADER_DIRS  "${CMAKE_SOURCE_DIR}/src/bsp/board")
set(FREERTOS_USAGE          "1")


message("${BoldRed}===============================[CMAKE SOURCE DIR         ]: ${CMAKE_SOURCE_DIR}      ${RESET}${White}")
message("${BoldRed}===============================[PROJECT     NAME         ]: ${PRJ_NAME}              ${RESET}${White}")
message("${BoldRed}===============================[PICO SDK PATH            ]: ${PICO_SDK_PATH}         ${RESET}${White}")
message("${BoldRed}===============================[PICO SDK EXTRAS PATH     ]: ${PICO_SDK_EXTRAS_PATH}  ${RESET}${White}")
message("${BoldRed}===============================[WIZNET DIR PATH          ]: ${WIZNET_DIR}            ${RESET}${White}")

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)                     # include(pico_sdk_import.cmake)
include(${PICO_SDK_EXTRAS_PATH}/external/pico_extras_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
	message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

if ( FREERTOS_USAGE )
	message("${BoldYellow}===============================[ FreeRTOS USE ]===============================${RESET}${White}")
	set(FREERTOS_KERNEL_PATH "${CMAKE_SOURCE_DIR}/src/lib/FreeRTOS-Kernel")
	include(${CMAKE_SOURCE_DIR}/src/lib/FreeRTOS_Kernel_import.cmake)
endif ()

project(${PRJ_NAME} C CXX ASM)

pico_sdk_init() # Initialize the SDK

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-Wno-maybe-uninitialized)
endif()


# Add blink example
add_subdirectory(src)
add_subdirectory(external)
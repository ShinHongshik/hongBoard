
# file(GLOB SRC_FILES  
file(GLOB SRC_FILES CONFIGURE_DEPENDS 
  # hw/*.c
  # ap/*.c
  # ap/*.cpp
  # bsp/*.c
  # bsp/rtos/*.c
  # hw/driver/*.c
  # common/core/*.c
  *.cpp
)

# file(GLOB_RECURSE SRC_FILES_RECURSE 
file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
  ap/*.cpp
  bsp/*.c
  common/*.c
  hw/*.c
  hw/driver/*.c
)





add_executable(
  ${PRJ_NAME}
  main.cpp

  ${SRC_FILES}
  ${SRC_FILES_RECURSE}
)


target_include_directories(${PRJ_NAME} PUBLIC
  ap
  ap/include
  bsp
  bsp/rtos 
  common
  common/core
  common/hw/include
  hw
  hw/driver
  lib

)


# pull in common dependencies
target_link_libraries(${PRJ_NAME} 
  cmsis_core
  pico_stdlib
  hardware_spi
  hardware_dma
  hardware_pio
  hardware_irq
  hardware_i2c
  hardware_flash
  hardware_adc
  pico_multicore

  TFTP_FILES
  ETHERNET_FILES
  SPI_FILES
  LOOPBACK_FILES 
  HTTPSERVER_FILES
  DHCP_FILES
  DNS_FILES
  TIMER_FILES
  SNTP_FILES
)

if (FREERTOS_USAGE)
  add_compile_definitions(FREERTOS_USE=${FREERTOS_USAGE})
  # add_compile_definitions(FREE_RTOS_KERNEL_SMP=1)
  # add_compile_definitions(portSUPPORT_SMP=1)

  target_link_libraries(${PRJ_NAME} 
    FreeRTOS-Kernel-Heap4
  )
endif ()

# target_compile_definitions(${PRJ_NAME}
  # FREE_RTOS_KERNEL_SMP=1
  # portSUPPORT_SMP=1
# )

# enable usb output, disable uart output
pico_enable_stdio_usb(${PRJ_NAME}  1)
pico_enable_stdio_uart(${PRJ_NAME}  1)

# create map/bin/hex/uf2 file etc.
add_subdirectory(lib/RP2040-HAT-C)

pico_add_extra_outputs(${PRJ_NAME})  

pico_set_linker_script(${PRJ_NAME} "${CMAKE_SOURCE_DIR}/src/bsp/ldscript/pico_flash.ld")

set_target_properties(${PRJ_NAME} PROPERTIES SUFFIX ".elf")

add_custom_command(TARGET ${PRJ_NAME} POST_BUILD
      COMMAND arm-none-eabi-size --format=berkeley --totals "$<TARGET_FILE:${PRJ_NAME}>"
      COMMENT "Invoking: Cross ARM GNU Print Size")

# ##############################################################################
# boards/arm/stm32/stm32f429i-disco/src/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

set(SRCS stm32_boot.c stm32_bringup.c stm32_spi.c)

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS stm32_autoleds.c)
endif()

if(CONFIG_ARCH_BUTTONS)
  list(APPEND SRCS stm32_buttons.c)
endif()

if(CONFIG_ARCH_IDLE_CUSTOM)
  list(APPEND SRCS stm32_idle.c)
endif()

if(CONFIG_STM32_FMC)
  list(APPEND SRCS stm32_extmem.c)
endif()

if(CONFIG_STM32_OTGHS)
  list(APPEND SRCS stm32_usb.c)
endif()

if(CONFIG_STM32F429I_DISCO_ILI9341)
  list(APPEND SRCS stm32_ili93414ws.c)
endif()

if(CONFIG_STM32F429I_DISCO_ILI9341_LCDIFACE
   AND CONFIG_STM32F429I_DISCO_ILI9341_FBIFACE
   AND CONFIG_STM32_LTDC)
  list(APPEND SRCS stm32_lcd.c)
endif()

if(CONFIG_PWM)
  list(APPEND SRCS stm32_pwm.c)
endif()

if(CONFIG_ADC)
  list(APPEND SRCS stm32_adc.c)
endif()

if(CONFIG_STM32_CAN_CHARDRIVER)
  list(APPEND SRCS stm32_can.c)
endif()

if(CONFIG_STM32F429I_DISCO_HIGHPRI)
  list(APPEND SRCS stm32_highpri.c)
endif()

if(CONFIG_STM32_SDIO)
  list(APPEND SRCS stm32_sdio.c)
endif()

if(CONFIG_STM32_LTDC)
  list(APPEND SRCS stm32_lcd.c)
endif()

if(CONFIG_MY_LED)
  list(APPEND SRCS stm32_myled.c)
endif()

if(CONFIG_MY_TOUCH)
  list(APPEND SRCS stm32_mytouch.c)
endif()

if(CONFIG_FAT_DMAMEMORY)
  list(APPEND SRCS stm32_dma_alloc.c)
endif()

if(CONFIG_MY_BUZZER)
  list(APPEND SRCS stm32_buzzer.c)
endif()

if(CONFIG_MY_INIY)
  list(APPEND SRCS stm32_myinit.c)
endif()

if(CONFIG_NXBOOT_BOOTLOADER)
  list(APPEND SRCS stm32_boot_image.c)
endif()

target_sources(board PRIVATE ${SRCS})

target_include_directories(board PRIVATE ${CMAKE_SOURCE_DIR}/arch/arm/src/stm32)

if(NOT CONFIG_BOOT_NXBOOT)
  set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/flat.ld")
elseif(CONFIG_NXBOOT_BOOTLOADER)
  set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/bootloader.ld")
else()
  # set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/flat.ld")
  set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/app.ld")
endif()


if(CONFIG_BOOT_NXBOOT AND NOT CONFIG_NXBOOT_BOOTLOADER)
  execute_process(
    COMMAND git -C ${CMAKE_SOURCE_DIR} describe --tags --dirty --always
    OUTPUT_VARIABLE NX_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )

  if(NOT NX_VERSION)
    set(NX_VERSION "0.0.0")
  endif()

  string(REGEX REPLACE "^v" "" NX_VERSION "${NX_VERSION}")
  string(REGEX REPLACE "-.*" "" NX_VERSION "${NX_VERSION}")

  if(NOT NX_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+")
    set(NX_VERSION "0.0.0")
  endif()

  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/nuttx.img
    COMMAND python3 ${NUTTX_APPS_DIR}/boot/nxboot/tools/nximage.py
            -v
            ${CMAKE_BINARY_DIR}/nuttx.bin
            ${CMAKE_BINARY_DIR}/nuttx.img
            --version ${NX_VERSION}
            --header_size ${CONFIG_NXBOOT_HEADER_SIZE}
            --identifier ${CONFIG_NXBOOT_PLATFORM_IDENTIFIER}
    DEPENDS ${CMAKE_BINARY_DIR}/nuttx.bin
    COMMENT "Generating nuttx.img"
  )

  add_custom_target(nxboot_img
    DEPENDS ${CMAKE_BINARY_DIR}/nuttx.img
  )

  if(NOT TARGET nuttx_post_build)
    add_custom_target(nuttx_post_build)
  endif()
  add_dependencies(nuttx_post_build nxboot_img)
endif()

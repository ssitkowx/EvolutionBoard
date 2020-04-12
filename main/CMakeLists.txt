set(srcs pretty_effect.c
         Logic/Project/Display.cpp
         Logic/Project/Peripheral/Spi.cpp
         Logic/Project/Peripheral/Gpio.cpp
         Hardware/main.c
         Hardware/MainCppHw.cpp
         Hardware/Peripheral/SpiHw.cpp
         Hardware/Peripheral/GpioHw.cpp
)

# Only ESP32 has enough memory to do jpeg decoding
if(IDF_TARGET STREQUAL "esp32")
    list(APPEND srcs "decode_image.c")
endif()

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS .
                       Logic/Project
                       Logic/Project/Peripheral
                       Hardware
                       Hardware/Peripheral
                       EMBED_FILES image.jpg)


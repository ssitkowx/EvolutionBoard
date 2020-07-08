set(srcs pretty_effect.c
         External/Lib/Utils/Utils.cpp
         External/Lib/Logger/Logger.cpp
         Logic/Project/Peripheral/Spi.cpp
         Logic/Project/Display/Display.cpp
         Logic/Project/Peripheral/Gpio.cpp
         Logic/Project/Peripheral/Rtos.cpp
         Hardware/main.c
         Hardware/MainCppHw.cpp
         Hardware/Display/ILI9341.cpp
         Hardware/Peripheral/SpiHw.cpp
         Hardware/Display/DisplayHw.cpp
         Hardware/Peripheral/RtosHw.cpp
         Hardware/Peripheral/GpioHw.cpp
)

# Only ESP32 has enough memory to do jpeg decoding
if(IDF_TARGET STREQUAL "esp32")
    list(APPEND srcs "decode_image.c")
endif()

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS 
                       .
                       External/Lib/Utils
                       External/Lib/Logger
                       Logic/Project
                       Logic/Project/Display
                       Logic/Project/Peripheral
                       Hardware
                       Hardware/Logger
                       Hardware/Display
                       Hardware/Peripheral
                       EMBED_FILES image.jpg)


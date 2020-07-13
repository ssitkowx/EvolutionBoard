set(srcs pretty_effect.c
         External/Lib/Utils/Utils.cpp
         External/Lib/Logger/Logger.cpp
         Logic/Project/Peripheral/Spi.cpp
         Logic/Project/Display/Display.cpp
         Logic/Project/Peripheral/Gpio.cpp
         Logic/Project/Peripheral/Rtos.cpp
         Logic/Project/Peripheral/Timer.cpp
         Logic/Project/Peripheral/SystemTime.cpp
         Logic/Project/Networking/WiFi.cpp
         Hardware/main.c
         Hardware/MainCppHw.cpp
         Hardware/Display/ILI9341.cpp
         Hardware/Display/DisplayHw.cpp
         Hardware/Peripheral/SpiHw.cpp
         Hardware/Peripheral/RtosHw.cpp
         Hardware/Peripheral/GpioHw.cpp
         Hardware/Peripheral/SystemTimeHw.cpp
         Hardware/Networking/WiFiHw.cpp
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
                       Logic/Project/Networking
                       Hardware
                       Hardware/Logger
                       Hardware/Display
                       Hardware/Peripheral
                       Hardware/Networking
                       EMBED_FILES image.jpg)


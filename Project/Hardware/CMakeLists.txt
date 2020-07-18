SET (PackageIncludePaths "C:/Users/sitko/.conan/download")
SET (PackageSourcePaths main.c
                        MainCppHw.cpp
                        Display/ILI9341.cpp
                        Display/DisplayHw.cpp
                        Peripheral/SpiHw.cpp
                        Peripheral/RtosHw.cpp
                        Peripheral/GpioHw.cpp
                        Peripheral/FlashHw.cpp
                        Peripheral/SystemTimeHw.cpp
                        Networking/WiFiHw.cpp
                        ../Logic/Settings.cpp
                        ${PackageIncludePaths}/Spi/Project/Spi.cpp
                        ${PackageIncludePaths}/WiFi/Project/WiFi.cpp
                        ${PackageIncludePaths}/Gpio/Project/Gpio.cpp
                        ${PackageIncludePaths}/Rtos/Project/Rtos.cpp
                        ${PackageIncludePaths}/Timer/Project/Timer.cpp
                        ${PackageIncludePaths}/Flash/Project/Flash.cpp
                        ${PackageIncludePaths}/Utils/Project/Utils.cpp
                        ${PackageIncludePaths}/Logger/Project/Logger.cpp
                        ${PackageIncludePaths}/Display/Project/Display.cpp
                        ${PackageIncludePaths}/SystemTime/Project/SystemTime.cpp
    )

IDF_COMPONENT_REGISTER (SRCS ${PackageSourcePaths}
                             INCLUDE_DIRS
                             .
                             Logger
                             Display
                             Peripheral
                             Networking
                             ../Logic
                             ${PackageIncludePaths}/Spi/Project
                             ${PackageIncludePaths}/WiFi/Project
                             ${PackageIncludePaths}/Gpio/Project
                             ${PackageIncludePaths}/Rtos/Project
                             ${PackageIncludePaths}/Timer/Project
                             ${PackageIncludePaths}/Flash/Project
                             ${PackageIncludePaths}/Utils/Project
                             ${PackageIncludePaths}/Logger/Project
                             ${PackageIncludePaths}/Display/Project
                             ${PackageIncludePaths}/SystemTime/Project
                             EMBED_FILES ../../External/Doc/Bitmaps/tiger.jpg
                             REQUIRES "nvs_flash"
                        )
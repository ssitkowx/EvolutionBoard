SET (PackageIncludePaths "C:/Users/sitko/.conan/download")
SET (PackageSourcePaths main.c
                        MainCppHw.cpp
                        Touch/TouchHw.cpp
                        Display/ILI9341.cpp
                        Display/DisplayHw.cpp
                        Peripheral/RtosHw.cpp
                        Peripheral/GpioHw.cpp
                        Peripheral/FlashHw.cpp
                        Peripheral/TimerHw.cpp
                        Peripheral/SpiHw/SpiHw.cpp
                        Peripheral/SystemTimeHw.cpp
                        Peripheral/SpiHw/SpiLcdHw.cpp
                        Peripheral/SpiHw/SpiTouchHw.cpp
                        Networking/WiFiHw.cpp
                        ../Logic/Settings.cpp
                        ${PackageIncludePaths}/Spi/Project/Spi.cpp
                        ${PackageIncludePaths}/WiFi/Project/WiFi.cpp
                        ${PackageIncludePaths}/Gpio/Project/Gpio.cpp
                        ${PackageIncludePaths}/Rtos/Project/Rtos.cpp
                        ${PackageIncludePaths}/Touch/Project/Touch.cpp
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
                             Touch
                             Peripheral
                             Networking
                             Peripheral/SpiHw
                             ../Logic
                             ../Logic/BitmapConverter/Images
                             ${PackageIncludePaths}/Spi/Project
                             ${PackageIncludePaths}/WiFi/Project
                             ${PackageIncludePaths}/Gpio/Project
                             ${PackageIncludePaths}/Rtos/Project
                             ${PackageIncludePaths}/Touch/Project
                             ${PackageIncludePaths}/Timer/Project
                             ${PackageIncludePaths}/Flash/Project
                             ${PackageIncludePaths}/Utils/Project
                             ${PackageIncludePaths}/Logger/Project
                             ${PackageIncludePaths}/Display/Project
                             ${PackageIncludePaths}/SystemTime/Project
                             EMBED_FILES ../../External/Doc/Bitmaps/tiger.jpg
                             REQUIRES "nvs_flash"
                        )
# EvolutionBoard

# I. Description:
The project was created to show selected capabilities of the ESP32-WROVER module.
The device shows the weather data on the display.

Equipment used:
- Display (240 x 320 with ILI9341 driver)) with Arduino Touch (Both using SPI and GPIO), 
- Time synchronization with the network and downloading weather data (WiFi, HTTPS),
- Free RTOS control (Semaphores and Event Groups),
- View heap and stack display.

Design pattern used:
- Abstract Factory, 
- Template Method, 
- Strategy, 
- CRTP, 
- Observer, 
- Singleton.

Tests:
The individual libraries as well as the entire project are tested with gtest and gmock (white-box approach).

P.S
All still under development.

# II. Assumptions & Structure:
Same as in AtollicTemplate project.

# III. Configuration:

- Eclipse IDE for C/C++ Developers. Version: 2020-06(4.16.0),
- ESP-IDF Branch_v4.0. Eclipse plugin configured according https://github.com/espressif/idf-eclipse-plugin/blob/master/README.md

# IV. Builidng:

Packages in External:
- The same as in the case of projects based on the "Template".

Project:
- Add to the project (in the CMakeLists.txt) files located in the ".conan\download" in the "External" folder,
- Add to the project (in the CMakeLists.txt) files located in the "Logic" and "Hardware" folders,
- Open a project gui and build a project.

# V. Tips:
- Remove '--no-site-packages' from idf_tool.py:
  - from: subprocess.check_call([sys.executable, '-m', 'virtualenv', '--no-site-packages', idf_python_env_path],
  - to:   subprocess.check_call([sys.executable, '-m', 'virtualenv', idf_python_env_path],
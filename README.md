# EvolutionBoard

# I. Description:
The project is used to show several capabilities of the ESP32 WROVER.
An example implementation is shown:
- time synchronization from the network (WiFi),
- downloading weather data from the cloud (WiFi + JOSN, POSTMAN),
- displaying weather data on the display (ILI9341, 2.8 '', SPI, 8bit 320x240) in real time,
- button operation using the Arduino touch.
- heap and stack busy display,
- tests with gmock and gtest.

The device works under RTOS control.

P.S
Device functionalities are incomplete yet(under development).

# II. Assumptions:
The code stored here is environment-specific, which means:
- The code depends on the environment in which it works,
- The code can use both generic and evironment-specific external libraries.

# III. Structure:
The embedded project has been divided into three parts:

External:
- This is where external generic libraries are stored,
- This is where documents and resources are stored.

Project:

- Logic:
  - This is where environment-specific but hardware-independent code is stored.

- Hardware:
  - This is where the environment-specific code is stored.

Tests:
- which uses gtest and/or gmock libraries.

# IV. Configuration:

- Eclipse IDE for C/C++ Developers. Version: 2020-06(4.16.0),
- ESP-IDF Branch_v4.0. Eclipse plugin configured according https://github.com/espressif/idf-eclipse-plugin/blob/master/README.md

# V. Builidng:

Packages in External:
- The same as in the case of projects based on the "Template".

Project:
- Add to the project (in the CMakeLists.txt) files located in the ".conan\download" in the "External" folder,
- Add to the project (in the CMakeLists.txt) files located in the "Logic" and "Hardware" folders,
- Open a project gui and build a project.

# VI. Tips:
- Remove '--no-site-packages' from idf_tool.py:
  - from: subprocess.check_call([sys.executable, '-m', 'virtualenv', '--no-site-packages', idf_python_env_path],
  - to:   subprocess.check_call([sys.executable, '-m', 'virtualenv', idf_python_env_path],
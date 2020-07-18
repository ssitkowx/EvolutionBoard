# EvolutionBoard

# I. Description:
Project is using:
- ESP32,
- LCD 2.8 in SPI 8bit configuration based on ILI9341 driver,
- Arduino touch.

Project has WiFi connection and is using Rtos.

# II. Assumptions:
The code stored here is environment-specific, which means:
- The code depends on the environment in which it works,
- The code can use both generic and evironment-specific external libraries.

# III. Structure:
The embedded project has been divided into three parts:

External:
- This is where external generic libraries are stored,
- This is where documents and resources are stored.

Logic:
- This is where environment-specific but hardware-independent code is stored.

Hardware:
- This is where the environment-specific code is stored.

# IV. Configuration:

- Eclipse IDE for C/C++ Developers. Version: 2020-06(4.16.0),
- ESP-IDF Branch_v4.0. Eclipse plugin configured according https://github.com/espressif/idf-eclipse-plugin/blob/master/README.md
- Generate hal libraries from CubeMx version 5.3.0,

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
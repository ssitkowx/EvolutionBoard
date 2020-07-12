# EvolutionBoard
# I. Description:
Project for testing a eight bits color display based on ESP32 and LCD 2.8 with ARDUINO touch keyboard.

# II. Assumptions:
- The code depends on the environment in which it works,
- The code can use external libraries independent of the environment,
- Low-level hall libraries are generated by CubeMx.

# III. Structure:
The embedded project has been divided into two parts:
Hardware:
- This is where the environment-specific code is kept.

Logic:
- This is where external libraries are stored,
- This is where environment-specific and hardware-independent code is stored.

# IV. Configuration:
- Eclipse IDE for C/C++ Developers. Version: 2019-12(4.14.0),
- ESP-IDF Eclipse plugin configured according https://github.com/espressif/idf-eclipse-plugin/blob/master/README.md
- Generate hal libraries from CubeMx version 5.3.0,
- To enable C++ settings add <nature>org.eclipse.cdt.core.ccnature</nature> to .project,
- Add files, folders and libraries to the 'eclipse' project.

# V. Builidng:
- Open a project gui and build a project.

# VI. Tips:
- Exclude 'main' from the build logic project.
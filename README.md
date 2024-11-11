# Particle Fluid simulator

<img align="right" width="550" src="https://github.com/000x999/000x999_gifs/blob/main/GHub_3_1.gif">


A 2D particle simulator written in C++ using Raylib. <br>The simulator features realistic particle physics, including collision handling and spatial optimization, An interactive GUI and multiple particle customization options.
<br><br><br>
**Features:**
- Verlet integration for smooth particle motion.
- Particle to particle collision detection using a spring-damping model.
- Spatial hashing to optimize collision detection.
- Mouse interaction for manipulating particles.
- Customizable particle appearance and colors.
- Multiple view modes including wireframe and collision vector viewing.
- Interactive GUI, manual particle customization and spawning.
- Semi realistic fluid simulation using particle collision vector rendering.
<br><br><br>
## How It Works:
- [A Comprehensive and in depth analysis of my particle simulator is available in a PDF format written in LaTeX.](https://github.com/000x999/ParticleFluid_Simulator/blob/main/Particle_Simulator_Analysis_000x999.pdf).
## **Notes**:
- The simulator now supports up to 11505 particles spawned at a constant 60FPS, roughly 3x the amount at it's initial release.
- The in depth analysis of my Particle Simulator is not currently up to date with the recent changes and only covers the initial release version. I will however update it, in due time.


## Requirements
- C++17 or newer
- MinGW/GCC/G++
- [Raylib](https://www.raylib.com/)

## Installation
**Note:**
- The particle simulator can be built and ran entirely in Visual Studio, the only requirement is having Raylib installed and the proper build commands and file paths linked in the project settings.
- Build instructions for anyone who doesn't use Visual studio can be found below including installing Raylib using vcpkg, MSYS2, Homebrew, apt as well as other build instructions and compiler flags.
- A Makefile is provided as well, simply insert your 'raylib/src' folder path in the CXXFLAGS and LDFLAGS sections inside the Makefile, ensure that 'raygui.h' is inside the src folder as well, then simply run 'make' from the command line.
- If all else fails, a pre-built executable is available to be downloaded. 

### Option 1: Install Raylib using **vcpkg**
1. Install vcpkg by cloning the repository:
    ```bash
    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    ./bootstrap-vcpkg.sh
    ```

2. Install Raylib using vcpkg:
    ```bash
    ./vcpkg install raylib
    ```

3. Integrate vcpkg with your development environment (CMake, Visual Studio, etc.):
    ```bash
    ./vcpkg integrate install
    ```

4. When building the project using CMake, specify the toolchain file:
    ```bash
    cmake -Bbuild -S. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
    cmake --build build
    ```

### Option 2: Install Raylib via Package Manager

#### On Windows (using MSYS2)
1. Install MSYS2 from [here](https://www.msys2.org/).
2. Open MSYS2 and run the following commands to install Raylib:
    ```bash
    pacman -Syu
    pacman -S mingw-w64-x86_64-raylib
    ```

#### On macOS (using Homebrew)
1. Install Homebrew if not already installed:
    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```
2. Install Raylib using Homebrew:
    ```bash
    brew install raylib
    ```

#### On Linux (using apt)
1. Install Raylib via the package manager:
    ```bash
    sudo apt-get install libraylib-dev
    ```

### Option 3: Manual Installation of Raylib
Follow the [official guide](https://github.com/raysan5/raylib) to manually build and install Raylib from source.

### Step 3: Clone the Repository and Build
1. Clone the repository:
    ```bash
    git clone https://github.com/000x999/ParticleFluid_Simulator
    cd ParticleFluid_Simulator
    ```
2. Compile and run the program directly from the command line:
    ```bash
    g++ -o ParticleFluid_Simulator main.cpp Particle.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -Wno-enum-compare -Wno-unused-variable -fpermissive
    ./ParticleFluid_Simulator
    ```
3. Compile and run using the provided Makefile:
    ```bash
    - Set your 'raylib/src' folder path in the CXXFLAGS and LDFLAGS section inside the Makefile. 
    - Double check that 'raygui.h' is inside the 'raylib/src' folder as well.
    - Simply run 'make' directly in the command line from within the 'ParticleFluid_Simulator' file.  
    ```


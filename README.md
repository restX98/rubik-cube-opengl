# Rubik's Cube

This is a 3D Rubik's Cube simulation implemented using OpenGL and GLFW. The project is built using CMake.

## Controls Summary

- **Face Rotation:**
  - `U` - Rotate the upper face clockwise.
  - `D` - Rotate the down face clockwise.
  - `L` - Rotate the left face clockwise.
  - `R` - Rotate the right face clockwise.
  - `B` - Rotate the back face clockwise.
  - `F` - Rotate the front face clockwise.
  - `Shift + (U, D, L, R, B, F)` - Rotate the selected face anti-clockwise.

- **Cube Orientation:**
  - `Space` - Turn the entire cube upside down.
  - `Left Arrow` - Rotate the cube to the left.
  - `Right Arrow` - Rotate the cube to the right.

- **View Control:**
  - `Right Mouse Button (Hold)` - Look behind the cube.
  - `Release Right Mouse Button` - Return to the normal view.

## Installation

### Prerequisites

- CMake 3.30 or higher
- OpenGL
- GLFW

### Building the Project

1. **Clone the repository:**

  ```bash
  git clone <repository-url>
  cd rubik-cube-opengl
  ```

2. **Create a build directory and navigate to it:**
```bash
mkdir build
cd build
```

3. **Generate the build files using CMake:**
```bash
cmake ..
```

4. **Build the project:**
```bash
cmake --build .
```
or
```bash
make
```

5. **Run the executable:**
```bash
./RubikCube
```

## Contributing
Feel free to submit issues and fork the repository to contribute to the project.

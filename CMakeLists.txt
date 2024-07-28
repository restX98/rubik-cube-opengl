cmake_minimum_required(VERSION 3.10)

project(RendeRest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
  FetchContent_Populate(glfw)

  set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
  set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
  set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
  set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()


# GLM
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/stb_image)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

add_executable(renderest
  src/main.cpp
  src/Window.cpp
  src/Shader.cpp
  src/Camera.cpp
  src/Mesh.cpp
  src/Model.cpp
  src/Square.cpp
)

target_link_libraries(renderest PRIVATE glfw glad stb_image glm::glm )

target_compile_definitions(renderest PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/")
target_compile_definitions(renderest PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

cmake_minimum_required(VERSION 3.12)
project(Flow)

# Find and configure GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# Find and configure GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Find and configure GLM (if not already installed)
# find_package(glm REQUIRED)
# include_directories(${GLM_INCLUDE_DIRS})

# Add your source files
add_executable(${PROJECT_NAME} main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
# target_link_libraries(${PROJECT_NAME} PRIVATE glm)

# Copy shaders to the build directory
configure_file(vertexShader.glsl vertexShader.glsl COPYONLY)
configure_file(fragmentShader.glsl fragmentShader.glsl COPYONLY)

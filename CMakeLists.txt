cmake_minimum_required(VERSION 3.12)
project(Flow)

set (CMAKE_CXX_STANDARD 20)

# Find and configure GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIR})

# Add your source files
add_executable(${PROJECT_NAME} src/main.cpp src/gl.c src/objectManager.cpp src/shapes/shape.cpp src/shapes/cube.cpp src/shapes/sphere.cpp src/hud/hud.cpp src/hud/crosshair.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE BulletDynamics BulletCollision LinearMath)

# Copy shaders to the build directory
configure_file(src/assets/hud.vs assets/hud.vs COPYONLY)
configure_file(src/assets/hud.fs assets/hud.fs COPYONLY)
configure_file(src/assets/directional_lighting.fs assets/directional_lighting.fs COPYONLY)
configure_file(src/assets/directional_lighting.vs assets/directional_lighting.vs COPYONLY)

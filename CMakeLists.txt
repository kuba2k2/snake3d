cmake_minimum_required(VERSION 3.24)

project(snake3d)

add_subdirectory("libs/glm/")
link_directories("libs/glew/lib/x64" "libs/glfw/lib/x64")
link_libraries(glew32 glew32s glfw3 opengl32 glm)

include_directories("src/" "models/" "libs/" "libs/glew/include" "libs/glfw/include")
file(GLOB SRCS "src/*.cpp" "libs/*.cpp")
add_executable(snake3d ${SRCS})

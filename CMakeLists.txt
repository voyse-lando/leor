CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(leor)

add_executable(leor src/main.c src/input_stream.c src/platform/io.c)
target_include_directories(leor PUBLIC include)
set_property(TARGET leor PROPERTY C_STANDARD_REQUIRED 23)

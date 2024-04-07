CMAKE_MINIMUM_REQUIRED(VERSION 3.21)

project(leor)

add_executable(leor src/main.c)
target_include_directories(leor PUBLIC include)
set_property(TARGET leor PROPERTY C_STANDARD_REQUIRED 23)

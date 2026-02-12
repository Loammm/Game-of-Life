cmake_minimum_required(VERSION 3.16)
project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put the compiled executable and libraries in the same folder,
# so the .dll / .so is right next to the .exe and it can find it.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# SDL3 is vendored as source code in vendored/SDL.
# EXCLUDE_FROM_ALL means "only build the parts we actually use".
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Our executable — just one source file for now.
add_executable(game_of_life WIN32 src/main.cpp)

# Link against SDL3.
target_link_libraries(game_of_life PRIVATE SDL3::SDL3)

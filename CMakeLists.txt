cmake_minimum_required(VERSION 3.16)
project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Our executable.
add_executable(game_of_life src/main.cpp src/grid.cpp)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    # Enable SDL3 in both compile and link stages
    target_compile_options(game_of_life PRIVATE
        "SHELL:-s USE_SDL=3"
    )
    target_link_options(game_of_life PRIVATE
        "SHELL:-s USE_SDL=3"
        "--shell-file" "${CMAKE_SOURCE_DIR}/shell.html"
    )
else()
    set_target_properties(game_of_life PROPERTIES WIN32_EXECUTABLE TRUE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
    target_link_libraries(game_of_life PRIVATE SDL3::SDL3)
endif()


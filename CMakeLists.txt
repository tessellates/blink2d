cmake_minimum_required(VERSION 3.10)

#LANGUAGES can be: C , CXX (i.e. C++)
project(blink2d VERSION 1.0
DESCRIPTION "2D engine -- for simple 2D games"
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#To prevent Apple frameworks from being included before brew installed packages
include_directories(BEFORE /usr/local/include)
set(CMAKE_FIND_FRAMEWORK LAST) 

#SDL
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2 REQUIRED)

# Create an executable and all files required to run it.
add_executable(${PROJECT_NAME}
    main.cpp
    )

# submodule
add_subdirectory(extern) 

# gui code
add_subdirectory(blinkgui) 

# model code
add_subdirectory(blinkmodel) 

# examples
add_subdirectory(examples) 

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    # Enable testing for the project.
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest ${CMAKE_SOURCE_DIR}/tests)

    # Include your tests subdirectory.
    add_subdirectory(tests)
endif()


#Link SDL
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image)

#Enable imgui default math operator
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)
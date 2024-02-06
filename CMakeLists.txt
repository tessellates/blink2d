cmake_minimum_required(VERSION 3.12)

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

find_package(OpenMP)


# Create the library
add_library(${PROJECT_NAME})

if (XCODE)
    # For xcode to see them
    file(GLOB_RECURSE XCODEHEADERS 
        ${CMAKE_SOURCE_DIR}/blinkgui/include/*.hpp  # This line will include all .hpp files in the include directory
        ${CMAKE_SOURCE_DIR}/blinkgui/include/rendering/*.hpp  # This line will include all .hpp files in the include directory
        ${CMAKE_SOURCE_DIR}/blinkmodel/include/*.hpp  # This line will include all .hpp files in the include directory
        ${CMAKE_SOURCE_DIR}/examples/snake/include/*.hpp  # This line will include all .hpp files in the include directory
        ${CMAKE_SOURCE_DIR}/examples/noitasim/*.hpp  # This line will include all .hpp files in the include directory
    )
    message("SETTING UP XCODE")
    target_sources(${PROJECT_NAME} PRIVATE ${XCODEHEADERS})
endif()

# Create an executable and its source file
add_executable(main
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



#Link SDL to the library
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image)
target_compile_options(${PROJECT_NAME} PRIVATE -Xclang -fopenmp)

#Link the library to an executable
target_link_libraries(main PUBLIC ${PROJECT_NAME})

#Enable imgui default math operator
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)


file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
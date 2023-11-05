add_subdirectory(src) 

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/examples/connect/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/examples/connect/include>
    $<INSTALL_INTERFACE:${CMAKE_PREFIX_PATH}/examples/connect/include>
)

add_subdirectory(src) 

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/blinkmodel/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/blinkmodel/include>
    $<INSTALL_INTERFACE:${CMAKE_PREFIX_PATH}/blinkmodel/include>
)
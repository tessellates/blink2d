add_subdirectory(src) 

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/blinkgui/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/blinkgui/include>
    $<INSTALL_INTERFACE:${CMAKE_PREFIX_PATH}/blinkgui/include>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/blinkgui/include/rendering>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/blinkgui/include/rendering>
    $<INSTALL_INTERFACE:${CMAKE_PREFIX_PATH}/blinkgui/include/rendering>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/blinkgui/include/gbuilders>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/blinkgui/include/gbuilders>
    $<INSTALL_INTERFACE:${CMAKE_PREFIX_PATH}/blinkgui/include/gbuilders>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/blinkgui/include/rendering/rendermanagers>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/blinkgui/include/rendering/rendermanagers>
    $<INSTALL_INTERFACE:${CMAKE_PREFIX_PATH}/blinkgui/include/rendering/rendermanagers>
)

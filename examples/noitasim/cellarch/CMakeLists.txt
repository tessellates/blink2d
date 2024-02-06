
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/examples/noitasim/cellarch>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/examples/noitasim/cellarch>
    $<INSTALL_INTERFACE:${CMAKE_PREFIX_PATH}/examples/noitasim/cellarch>
)

target_sources(${PROJECT_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/CellManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PhasedWalkProcessor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/WalkCalculator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OneWalkProcessor.cpp
)


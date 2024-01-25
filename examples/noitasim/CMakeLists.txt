
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/examples/noitasim>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/examples/noitasim>
    $<INSTALL_INTERFACE:${CMAKE_PREFIX_PATH}/examples/noitasim>
)

target_sources(${PROJECT_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/ColorTextureManager.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/NoitaSimModel.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/NoitaSimGui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/NoitaSimGame.cpp
)


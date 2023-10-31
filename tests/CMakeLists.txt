include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


function(add_gtest_test TEST_NAME)
    # Create an executable for the test source file.
    add_executable(${TEST_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.cpp)
    
    # Link the necessary libraries.
    target_link_libraries(${TEST_NAME} gtest gtest_main ${PROJECT_NAME})

    # Register the executable as a test.
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_subdirectory(snake)

add_gtest_test(google_test_test)

# Link GoogleTest and your own library (if applicable) to your test executable.
#target_link_libraries(my_tests GTest::GTest GTest::Main your_library_if_needed)


include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# Gather your source files for your tests.
set(TEST_SOURCES
    google_test_test.cpp
    # ... any additional test files ...
)

# Create a test executable.
add_executable(my_tests ${TEST_SOURCES} )
target_link_libraries(my_tests gtest gtest_main)

# Link GoogleTest and your own library (if applicable) to your test executable.
#target_link_libraries(my_tests GTest::GTest GTest::Main your_library_if_needed)

# Register the tests with CTest.
add_test(UnitTests my_tests)
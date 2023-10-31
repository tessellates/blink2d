# CMake generated Testfile for 
# Source directory: /Users/tobiash/Projects/DearUI/Blink2D/tests
# Build directory: /Users/tobiash/Projects/DearUI/Blink2D/XcodeProject/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(google_test_test "/Users/tobiash/Projects/DearUI/Blink2D/XcodeProject/tests/Debug/google_test_test")
  set_tests_properties(google_test_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;12;add_test;/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;17;add_gtest_test;/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(google_test_test "/Users/tobiash/Projects/DearUI/Blink2D/XcodeProject/tests/Release/google_test_test")
  set_tests_properties(google_test_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;12;add_test;/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;17;add_gtest_test;/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(google_test_test "/Users/tobiash/Projects/DearUI/Blink2D/XcodeProject/tests/MinSizeRel/google_test_test")
  set_tests_properties(google_test_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;12;add_test;/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;17;add_gtest_test;/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(google_test_test "/Users/tobiash/Projects/DearUI/Blink2D/XcodeProject/tests/RelWithDebInfo/google_test_test")
  set_tests_properties(google_test_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;12;add_test;/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;17;add_gtest_test;/Users/tobiash/Projects/DearUI/Blink2D/tests/CMakeLists.txt;0;")
else()
  add_test(google_test_test NOT_AVAILABLE)
endif()
subdirs("snake")

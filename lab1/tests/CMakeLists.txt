add_executable(run_tests test_main.cpp)

target_link_libraries(run_tests PRIVATE find_numbers_lib gtest_main)
target_include_directories(run_tests PUBLIC ../src)
include(GoogleTest)
gtest_add_tests(TARGET run_tests)
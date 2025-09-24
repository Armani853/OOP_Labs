add_executable(run_tests test_main.cpp)

target_link_libraries(run_tests PRIVATE find_numbers_lib gtest_main)

include(GoogleTest)
gtest_add_tests(TARGET run_tests)
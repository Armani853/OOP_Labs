add_library(find_numbers_lib STATIC
    find_numbers.cpp
    find_numbers.h
)

target_include_directories(find_numbers_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(lab1 main.cpp)

target_link_libraries(lab1 PRIVATE find_numbers_lib)
cmake_minimum_required(VERSION 3.2)

project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#project(matrix VERSION 0.0.1)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(matrix matrix.h matrix.cpp)
add_executable(matrix_test matrix_test.cpp)

set_target_properties(matrix_test PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON 
)

set_target_properties(matrix PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON 
)

target_include_directories(matrix_test
    PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(matrix_test
    ${GTEST_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if (MSVC)
    target_compile_options(matrix PRIVATE
        /W4
    )
    target_compile_options(matrix_test PRIVATE
        /W4
    )
else ()
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(matrix_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example.example@gmail.com)

include(CPack)

enable_testing()

add_test(matrix_test matrix_test)
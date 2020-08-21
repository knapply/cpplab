
# include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
# doctest_discover_tests(cpplabTests)

# ---- code coverage ----

set(CMAKE_CXX_STANDARD 17)


target_compile_options(cpplab INTERFACE -O0 -g -std=gnu++17 -fprofile-arcs -ftest-coverage)
target_link_options(cpplab INTERFACE -fprofile-arcs -ftest-coverage)


# cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# # project(cpplabTests
# #   LANGUAGES CXX
# # )

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)


# # set(CMAKE_MACOSX_RPATH OFF)
# # option(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# # ---- Options ----

# option(ENABLE_TEST_COVERAGE "Enable test coverage" ON)
# option(TEST_INSTALLED_VERSION "Test the version found by find_package" ON)

# # ---- Dependencies ----

# include(../cmake/CPM.cmake)

# # CPMAddPackage(
# #   NAME doctest
# #   GITHUB_REPOSITORY onqtam/doctest
# #   GIT_TAG 2.3.7
# # )


# CPMAddPackage(
#     NAME cpplab
#     SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
# )

# # CPMAddPackage(
# #   NAME Format.cmake
# #   GITHUB_REPOSITORY TheLartians/Format.cmake
# #   VERSION 1.4
# # )

# # # ---- Create binary ----

# # file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
# # add_executable(cpplabTests ${sources})
# # target_link_libraries(cpplabTests doctest cpplab)

# # set_target_properties(cpplabTests PROPERTIES CXX_STANDARD 17)

# # # enable compiler warnings
# # if (NOT TEST_INSTALLED_VERSION)
# #   if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
# #     target_compile_options(cpplab INTERFACE -Wall -pedantic -Wextra -Werror)
# #   elseif(MSVC)
# #     target_compile_options(cpplab INTERFACE /W4 /WX)
# #   endif()
# # endif()

# # # ---- Add cpplabTests ----

# enable_testing() 

# # # Note: doctest and similar testing frameworks can automatically configure CMake tests
# # # For other testing frameworks add the tests target instead:
# # # ADD_TEST(cpplabTests cpplabTests)

# include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
# doctest_discover_tests(cpplabTests)

# # # ---- code coverage ----

# # if (ENABLE_TEST_COVERAGE)
# #   target_compile_options(cpplab INTERFACE -O0 -g -std=gnu++17 -fprofile-arcs -ftest-coverage)
# #   target_link_options(cpplab INTERFACE -fprofile-arcs -ftest-coverage)
# # endif()

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

# Note: update this to your new project's name and version
project(cpplab 
  VERSION 0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# option(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# --- Import tools ----

include(cmake/tools.cmake)
include(CTest)
enable_testing()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.0
)

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.4
)

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY onqtam/doctest
  GIT_TAG 2.3.7
)



if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bench/benchmark)
execute_process (
  COMMAND bash -c "
  cd ${CMAKE_CURRENT_SOURCE_DIR}/bench
  git clone https://github.com/google/benchmark.git
  git clone https://github.com/google/googletest.git benchmark/googletest
  cd ${CMAKE_CURRENT_SOURCE_DIR}/bench/benchmark
  cmake -E make_directory \"build\"
  cmake -E chdir \"build\" cmake -DCMAKE_BUILD_TYPE=Release ../
  cmake --build \"build\" --config Release
  cd ${CMAKE_CURRENT_SOURCE_DIR}"
)
endif()
# ---- Add source files ----

FILE(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
FILE(GLOB_RECURSE headers2 CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

# ---- Create library ----

add_library(cpplabHeaders EXCLUDE_FROM_ALL ${headers} ${headers2})
set_target_properties(cpplabHeaders PROPERTIES LINKER_LANGUAGE CXX)

# set_property(COMPILE_FEATURES cxx_std_17)

add_library(cpplab INTERFACE)
set_target_properties(cpplab PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_17)

# beeing a cross-platform target, we enforce enforce standards conformance on MSVC
target_compile_options(cpplab INTERFACE "$<$<BOOL:${MSVC}>:/permissive->")

target_include_directories(cpplab
INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)



# ---- Create an installable target ----
packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
)








cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project(
#     cpplabTests
#     LANGUAGES CXX
# )

# set(CMAKE_CLANG_TIDY ON)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# option(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" ON)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" ON)

# ---- Dependencies ----

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include") 


# CPMAddPackage(
#     NAME cpplab
#     SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
# )

# CPMAddPackage(
#   NAME doctest
#   GITHUB_REPOSITORY onqtam/doctest
#   GIT_TAG 2.3.7
# )


# CPMAddPackage(
#   NAME Format.cmake
#   GITHUB_REPOSITORY TheLartians/Format.cmake
#   VERSION 1.4
# )

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/source/*.cpp)
add_executable(${PROJECT_NAME}-test ${sources})
target_link_libraries(${PROJECT_NAME}-test doctest cpplab)

set_target_properties(${PROJECT_NAME}-test PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if (NOT TEST_INSTALLED_VERSION)
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(cpplab INTERFACE -Wall -pedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(cpplab INTERFACE /W4 /WX)
  endif()
endif()

# ---- Add cpplabTests ----

# enable_testing() 

# Note: doctest and similar testing frameworks can automatically configure CMake tests
# For other testing frameworks add the tests target instead:
# ADD_TEST(cpplabTests cpplabTests)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${PROJECT_NAME}-test)

# # ---- code coverage ----

# if (ENABLE_TEST_COVERAGE)
#   target_compile_options(cpplab INTERFACE -O0 -g -std=gnu++17 -fprofile-arcs -ftest-coverage)
#   target_link_options(cpplab INTERFACE -fprofile-arcs -ftest-coverage)
# endif()


# set(benchmark_src benchmark/cpplab-bench.cpp)

# add_executable(benchmark ${benchmark_src})

# # add_subdirectory(benchmark)
# add_subdirectory(benchmark/benchmark)
# target_link_libraries(benchmark PUBLIC include)

cmake_minimum_required (VERSION 3.0.2)
project (DerivativeSolver)

include(CheckCXXCompilerFlag)
function(check_and_set_compiler_flag flag_name)
   check_cxx_compiler_flag(${flag_name} isFlagSupported)
   message(STATUS "Support of compiler flag ${flag_name} is ${isFlagSupported}")
   if(${isFlagSupported})
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag_name}")
      add_compile_options(${flag_name})
   endif()
endfunction()

# version
set(DerivativeSolver_VERSION_MAJOR 0)
set(DerivativeSolver_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# force essential compiler options if they are supported
check_and_set_compiler_flag("-Wall")
check_and_set_compiler_flag("-Werror")
check_and_set_compiler_flag("-Wextra")
check_and_set_compiler_flag("-pedantic")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_COMPILER_IS_GNUCC) 
        check_and_set_compiler_flag("-O0")
        check_and_set_compiler_flag("--coverage")
    else()
        # TODO coverage for clang?
    endif()
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/src/MathParser
                 ${CMAKE_BINARY_DIR}/src/MathParser/build)

add_executable(DerivativeSolver
    src/Differentiator.cpp
    src/main.cpp
    src/OptimizationRule.cpp
    src/Optimizer.cpp
    src/SolverApplication.cpp
    src/SumConstantsRule.cpp
    src/SumIdenticalExpressionsRule.cpp
    src/SumWithNullArgumentRule.cpp
    src/MultConstantsRule.cpp
    src/MultIdenticalExpressionsRule.cpp
    src/PowConstantRule.cpp
    src/PowOfPowRule.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_COMPILER_IS_GNUCC) 
        set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --coverage" )
        target_link_libraries (DerivativeSolver gcov)
    else()
        # TODO coverage for clang?
    endif()
endif()

target_link_libraries(DerivativeSolver libagmathparser)
target_include_directories(DerivativeSolver PUBLIC
   $<BUILD_INTERFACE:${MathParser_SOURCE_DIR}/src>
   $<INSTALL_INTERFACE:include/libagmathparser>
)

# code snippet to incorporate google test library for unit tsting
# ---------------------------------
if (NOT TARGET gtest)
    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.gtest googletest-download/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
       RESULT_VARIABLE result
       WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-download 
    )
    if(result)
       message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
       RESULT_VARIABLE result
       WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-download 
    )
    if(result)
       message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${PROJECT_BINARY_DIR}/googletest-src
                     ${PROJECT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
      include_directories("${gtest_SOURCE_DIR}/include")
    endif()
# ---------------------------------
endif()

function(add_unit_test_suite) 
   get_filename_component(test_suite_name ${ARGV0} NAME_WE)
   add_executable(${test_suite_name} ${ARGV})
   target_link_libraries(${test_suite_name} gtest_main libagmathparser)

   if(CMAKE_BUILD_TYPE STREQUAL "Debug")
       if(CMAKE_COMPILER_IS_GNUCC) 
           set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --coverage" )
           target_link_libraries (${test_suite_name} gcov)
       else()
       # TODO coverage for clang?
       endif()
   endif()

   target_include_directories(${test_suite_name} PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
      $<BUILD_INTERFACE:${MathParser_SOURCE_DIR}/src>
      $<INSTALL_INTERFACE:include/libagmathparser>
   )
   add_test(NAME ${test_suite_name} COMMAND ${test_suite_name} --gtest_shuffle --gtest_repeat=7)
endfunction()

add_unit_test_suite("test/DifferentiatorTest.cpp" "src/Differentiator.cpp")
add_unit_test_suite("test/OptimizerTest.cpp" 
    "src/Optimizer.cpp" 
    "src/SumConstantsRule.cpp" 
    "src/SumWithNullArgumentRule.cpp" 
    "src/SumIdenticalExpressionsRule.cpp" 
    "src/MultConstantsRule.cpp"
    "src/MultIdenticalExpressionsRule.cpp"
    "src/OptimizationRule.cpp"
    "src/PowConstantRule.cpp"
    "src/PowOfPowRule.cpp"
)
add_unit_test_suite("test/SumConstantsRuleTest.cpp" "src/SumConstantsRule.cpp" "src/OptimizationRule.cpp")
add_unit_test_suite("test/SumWithNullArgumentRuleTest.cpp" "src/SumWithNullArgumentRule.cpp" "src/OptimizationRule.cpp")
add_unit_test_suite("test/SumIdenticalExpressionsRuleTest.cpp" "src/SumIdenticalExpressionsRule.cpp" "src/OptimizationRule.cpp")
add_unit_test_suite("test/MultConstantsRuleTest.cpp" "src/MultConstantsRule.cpp" "src/OptimizationRule.cpp")
add_unit_test_suite("test/MultIdenticalExpressionsRuleTest.cpp" "src/MultIdenticalExpressionsRule.cpp" "src/OptimizationRule.cpp")
add_unit_test_suite("test/PowConstantRuleTest.cpp" "src/PowConstantRule.cpp" "src/OptimizationRule.cpp")
add_unit_test_suite("test/PowOfPowRuleTest.cpp" "src/PowOfPowRule.cpp" "src/OptimizationRule.cpp")

enable_testing ()

# ---------------------------------

install(TARGETS DerivativeSolver DESTINATION bin)

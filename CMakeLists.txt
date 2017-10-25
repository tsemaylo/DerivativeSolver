cmake_minimum_required (VERSION 3.0.2)
project (DerivativeSolver)

# definitions of custom functions
# ----------------------------------------
include(CheckCXXCompilerFlag)
function(check_and_set_compiler_flag flag_name)
    check_cxx_compiler_flag(flag_name isFlagSupported)
    if(isFlagSupported)
       set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag_name}")
    endif()
endfunction()

function(add_prefix var prefix)
   set(listVar "")
   foreach(f ${ARGN})
      list(APPEND listVar "${prefix}/${f}")
   endforeach(f)
   set(${var} "${listVar}" PARENT_SCOPE)
endfunction()

# end of custom functions definitions ----

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

add_subdirectory(${CMAKE_SOURCE_DIR}/src/MathParser
                 ${CMAKE_BINARY_DIR}/src/MathParser/build)

add_executable(DerivativeSolver
    src/Differentiator.cpp
    src/main.cpp
    src/OptimizationRule.cpp
    src/Optimizer.cpp
    src/SolverApplication.cpp
    src/SumConstantsRule.cpp
    src/SumWithNullArgumentRule.cpp
)

message(STATUS "MathParser_BUILD_DIR = ${MathParser_BUILD_DIR}")

target_link_libraries(DerivativeSolver libagmathparser)
target_include_directories(DerivativeSolver PUBLIC
   $<BUILD_INTERFACE:${MathParser_SOURCE_DIR}/src>
   $<INSTALL_INTERFACE:include/libagmathparser>
)

# ---------------------------------

install(TARGETS DerivativeSolver DESTINATION bin)
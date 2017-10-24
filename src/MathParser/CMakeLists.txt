cmake_minimum_required (VERSION 3.0)
project (MathParser)

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

function(add_unit_test_suite test_suite_name)
    add_executable(${test_suite_name} "test/${test_suite_name}.cpp")
    target_link_libraries(${test_suite_name} gtest_main libagmathparser)
    target_include_directories(${test_suite_name} PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
      $<INSTALL_INTERFACE:include>
    )
    add_test(NAME ${test_suite_name} COMMAND ${test_suite_name})
endfunction()

# end of custom functions definitions ----

# version
set(MathParser_VERSION_MAJOR 0)
set(MathParser_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# force essential compiler options if they are supported
check_and_set_compiler_flag("-Wall")
check_and_set_compiler_flag("-Werror")
check_and_set_compiler_flag("-Wextra")
check_and_set_compiler_flag("-pedantic")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

aux_source_directory(src allSources)
add_library(libagmathparser ${allSources})

add_prefix(public_headers "src/" "Pointers.h" "Parser.h" "ParserFactory.h" "ExpressionFactory.h" "Constant.h" "Variable.h" "Sum.h" "Sub.h" "Div.h" "Mult.h" "Pow.h" "Sin.h" "Cos.h" "Tan.h" "Ctan.h" "Ln.h" "Exp.h" "Expression.h" "Visitor.h" "TraverseException.h" "ParsingException.h")


# code snippet to incorporate google test library for unit tsting
# ---------------------------------
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()
# ---------------------------------

# Defining the list of unit test suits

file(GLOB test_suites "test/*.cpp")
foreach(suite_file_name ${test_suites})
   get_filename_component(suite_name ${suite_file_name} NAME_WE)
   add_unit_test_suite(${suite_name})
endforeach()

enable_testing ()

install(TARGETS libagmathparser DESTINATION lib)
install(FILES ${public_headers} DESTINATION include)
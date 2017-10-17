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

install(TARGETS libagmathparser DESTINATION lib)
install(FILES ${public_headers} DESTINATION include)
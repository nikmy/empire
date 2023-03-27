cmake_minimum_required(VERSION 3.10)

set(
        PROJECT_NAME
        empire_compiler
)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
        HEADERS
        ${CMAKE_SOURCE_DIR}/grammar/driver.hh
        ${CMAKE_SOURCE_DIR}/grammar/parser.hh
)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

BISON_TARGET(
        MyParser
        ${CMAKE_SOURCE_DIR}/grammar/parser.y
        ${CMAKE_SOURCE_DIR}/grammar/parser.cpp
        DEFINES_FILE ${CMAKE_SOURCE_DIR}/grammar/parser.hh
        COMPILE_FLAGS --graph
        VERBOSE ${CMAKE_SOURCE_DIR}/grammar/found_conflicts.txt
)

FLEX_TARGET(
        MyScanner
        ${CMAKE_SOURCE_DIR}/grammar/scanner.l
        ${CMAKE_SOURCE_DIR}/grammar/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "llvm include: ${LLVM_INCLUDE_DIRS}")

add_executable(
        ${PROJECT_NAME}
        main.cpp
        driver.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)

target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/llvm-12)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE

        ${CMAKE_SOURCE_DIR}
        grammar
        ast
        ast/tree
        ast/tree/declaration
        ast/tree/expression
        ast/tree/statement
        ast/tree/type
        ast/tree/lvalue
        ast/tree/cmd
        ast/visit
        runtime/
)

set(
        GRAMMAR_SOURCES

        grammar/parser.cpp
        grammar/scanner.cpp
)

set(
        OBJECT_SOURCES

        runtime/object.hpp
        runtime/type_info.hpp

        driver.cpp
)

set(
        AST_SOURCES

        ast/tree/cmd/program.hpp
        ast/tree/cmd/main_func.hpp
        ast/tree/node.hpp
        ast/forward_decl.hpp
        ast/include_list.hpp

        ast/tree/expression/expression.hpp
        ast/tree/expression/expression_list.hpp
        ast/tree/expression/binary_op.hpp
        ast/tree/expression/function_call.hpp

        ast/tree/expression/integer.hpp
        ast/tree/expression/bool.hpp
        ast/tree/expression/identifier.hpp

        ast/tree/expression/and.hpp
        ast/tree/expression/not.hpp
        ast/tree/expression/or.hpp

        ast/tree/expression/add.hpp
        ast/tree/expression/sub.hpp
        ast/tree/expression/mul.hpp
        ast/tree/expression/div.hpp
        ast/tree/expression/mod.hpp

        ast/tree/expression/equal.hpp
        ast/tree/expression/less.hpp
        ast/tree/expression/less_equal.hpp
        ast/tree/expression/greater.hpp
        ast/tree/expression/greater_equal.hpp

        ast/tree/statement/statement.hpp
        ast/tree/statement/statement_list.hpp

        ast/tree/statement/var_decl_stmt.hpp
        ast/tree/statement/assignment.hpp
        ast/tree/statement/if.hpp
        ast/tree/statement/if_else.hpp
        ast/tree/statement/while.hpp
        ast/tree/statement/print.hpp
        ast/tree/statement/function_call_stmt.hpp

        ast/tree/type/type.hpp
        ast/tree/type/basic_type.hpp

        ast/tree/declaration/declaration.hpp
        ast/tree/declaration/declaration_list.hpp
        ast/tree/declaration/func_decl.hpp
        ast/tree/declaration/var_decl.hpp
        ast/tree/declaration/formal_arg.hpp
        ast/tree/declaration/formal_arg_list.hpp

        ast/tree/lvalue/lvalue.hpp
        ast/tree/lvalue/reference.hpp
)

set(
        VISITORS_SOURCES

        ast/visit/visitor.hpp
        ast/visit/template_visitor.hpp
        ast/visit/printer.hpp
        ast/visit/interpreter.hpp
        ast/visit/ir_builder.hpp

        ast/visit/printer.cpp
        ast/visit/interpreter.cpp
        ast/visit/ir_builder.cpp
)

set(SOURCES ${AST_SOURCES} ${GRAMMAR_SOURCES} ${VISITORS_SOURCES})

target_sources(
        ${PROJECT_NAME}
        PRIVATE
        main.cpp
        ${SOURCES}
)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(${PROJECT_NAME} ${llvm_libs})
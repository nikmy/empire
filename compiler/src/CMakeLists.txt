cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0076 NEW)

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

add_executable(
        ${PROJECT_NAME}
        main.cpp
        driver.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)

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
        AST_SOURCES

        ast/tree/cmd/program.hpp
        ast/tree/cmd/main_func.hpp
        ast/tree/node.hpp
        ast/forward_decl.hpp
        ast/include_list.hpp

        ast/tree/expression/expression.hpp
        ast/tree/expression/expression_list.hpp
        ast/tree/expression/binary_op.hpp

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

        ast/tree/type/type.hpp
        ast/tree/type/basic_type.hpp

        ast/tree/declaration/declaration.hpp
        ast/tree/declaration/var_decl.hpp

        ast/tree/lvalue/lvalue.hpp
        ast/tree/lvalue/reference.hpp
)

set(
        VISITORS_SOURCES

        ast/visit/visitor.hpp
        ast/visit/printer.hpp
        ast/visit/interpreter.hpp

        ast/visit/printer.cpp
        ast/visit/interpreter.cpp
)

target_sources(
        ${PROJECT_NAME}
        PRIVATE

        ${AST_SOURCES}

        grammar/parser.cpp
        grammar/scanner.cpp

        ${VISITORS_SOURCES}

        runtime/object.hpp
        runtime/type_info.hpp

        main.cpp
        driver.cpp
)
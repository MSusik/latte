cmake_minimum_required(VERSION 3.3)
project(Latte)

find_package(Boost REQUIRED COMPONENTS system filesystem)

SET (CMAKE_CXX_COMPILER             "/usr/bin/g++")
SET (CMAKE_CXX_FLAGS                "-std=c++11 -g")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(COMPILER_DIR ${CMAKE_SOURCE_DIR}/src/compiler)

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_SOURCE_DIR}/src/Parser.C)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
            OUTPUT ${BisonOutput}
            COMMAND ${BISON_EXECUTABLE}
            --output=${BisonOutput}
            ${CMAKE_SOURCE_DIR}/src/Latte.y
            COMMENT "Generating parser.C"
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/src/Lexer.C)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
            OUTPUT ${FlexOutput}
            COMMAND ${FLEX_EXECUTABLE}
            --outfile=${FlexOutput}
            ${CMAKE_SOURCE_DIR}/src/Latte.l
            COMMENT "Generating lexer.C"
    )
ENDIF()

SET_SOURCE_FILES_PROPERTIES(${CMAKE_SOURCE_DIR}/src/Lexer.C GENERATED)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_SOURCE_DIR}/src/Parser.C GENERATED)
set(SOURCE_FILES src/Absyn.C src/Absyn.H src/Lexer.C src/Parser.C src/Parser.H src/Printer.C src/Printer.H)


# Compile Test Latte
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
add_executable(TestLatte ${SOURCE_FILES} src/Test.C)

# Compile compiler
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(COMPILER_SOURCES ${COMPILER_DIR}/main.cpp ${COMPILER_DIR}/Skeleton.C ${COMPILER_DIR}/Skeleton.H
        ${COMPILER_DIR}/CorrectnessChecker.C ${COMPILER_DIR}/CorrectnessChecker.H ${COMPILER_DIR}/utils.cpp
        ${COMPILER_DIR}/TypeFetcher.C ${COMPILER_DIR}/TypeFetcher.H
        ${COMPILER_DIR}/utils.h src/compiler/FunctionRetriever.cpp src/compiler/FunctionRetriever.h src/compiler/Environment.cpp src/compiler/Environment.h src/compiler/Compiler.cpp src/compiler/Compiler.h src/compiler/CompilerEnvironment.cpp src/compiler/CompilerEnvironment.h)
add_executable(latc_x86_64 ${SOURCE_FILES} ${COMPILER_SOURCES})
TARGET_LINK_LIBRARIES(latc_x86_64 ${Boost_LIBRARIES})

cmake_minimum_required(VERSION 3.8)
project(LISPIntepreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        LispIntepreter/main.cpp
        LispIntepreter/Parser.cpp
        LispIntepreter/Parser.h LispIntepreter/ParseException.cpp LispIntepreter/ParseException.h)

add_executable(LISPIntepreter ${SOURCE_FILES})
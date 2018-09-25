cmake_minimum_required(VERSION 3.8)
project(LISPIntepreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        LispIntepreter/main.cpp
        LispIntepreter/Parser.cpp
        LispIntepreter/Parser.h LispIntepreter/ParseException.cpp LispIntepreter/ParseException.h LispIntepreter/LispNode.cpp LispIntepreter/LispNode.h LispIntepreter/LispFunction.cpp LispIntepreter/LispFunction.h LispIntepreter/LispConstant.cpp LispIntepreter/LispConstant.h
        LispIntepreter/LispKeyWord.cpp LispIntepreter/LispName.cpp LispIntepreter/ReturnValue.cpp LispIntepreter/EvalException.cpp LispIntepreter/EvalException.h)

add_executable(LISPIntepreter ${SOURCE_FILES})
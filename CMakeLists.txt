cmake_minimum_required(VERSION 4.0)
project(lepai)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lepai src/main.cpp
        include/tokenizer/tokenizer.h
        src/tokenizer/tokenizer.cpp
        include/parser/node.h
        src/parser/node.cpp
        include/parser/fx_parser.h
        src/parser/fx_parser.cpp
        include/utils/utils.h
        src/utils/utils.cpp
        include/utils/converters.h
        src/utils/converters.cpp
)

add_executable(cnfchk src/benchmark.cpp
        include/tokenizer/tokenizer.h
        src/tokenizer/tokenizer.cpp
        include/parser/node.h
        src/parser/node.cpp
        include/parser/fx_parser.h
        src/parser/fx_parser.cpp
        include/utils/utils.h
        src/utils/utils.cpp
        include/utils/converters.h
        src/utils/converters.cpp
)

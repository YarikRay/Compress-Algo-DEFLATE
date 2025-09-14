cmake_minimum_required(VERSION 3.31)
project(DEFLATE)

# Явно указываем путь к zlib для MinGW
set(ZLIB_ROOT "C:/mingw/mingw64/x86_64-w64-mingw32/")

set(ZLIB_INCLUDE "${ZLIB_ROOT}/include")
set(CMAKE_PREFIX_PATH "${ZLIB_ROOT}")

# Ищем zlib
find_package(ZLIB REQUIRED)
find_package(libdeflate REQUIRED)



set(CMAKE_CXX_STANDARD 20)



add_executable(DEFLATE
        main.cpp
        miniz-3.0.2/miniz.c
        miniz-3.0.2/miniz.h
        headers/zlib_test.h
        sources/zlib_test.cpp
        sources/compress2.cpp
        sources/time_def.cpp
        headers/time_def.h
        sources/path.cpp
        headers/path.h
        sources/m_compress.cpp
        sources/libdeflate.cpp
)

target_link_libraries(DEFLATE PRIVATE libdeflate)
target_link_libraries(DEFLATE PRIVATE ZLIB::ZLIB)
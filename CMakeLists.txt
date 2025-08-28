cmake_minimum_required(VERSION 3.31)
project(DEFLATE)

# Явно указываем путь к zlib для MinGW
set(ZLIB_ROOT "C:/msys64/mingw64")
set(CMAKE_PREFIX_PATH "${ZLIB_ROOT}")

# Ищем zlib
find_package(ZLIB REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(DEFLATE
        main.cpp
        zlib_test.h
        zlib_test.cpp
        compress2.cpp
        time_def.cpp
        time_def.h
        path.cpp
)

# Правильные варианты линковки zlib
if(TARGET ZLIB::ZLIB)
    target_link_libraries(DEFLATE PRIVATE ZLIB::ZLIB)
else()
    # Для MinGW используется просто 'z'
    target_link_libraries(DEFLATE PRIVATE z)
endif()
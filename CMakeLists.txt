cmake_minimum_required(VERSION 3.29)
project(wuziqi)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_STANDARD 20)
set(EASYX_DIR D:/env/easyx4mingw_20240601)

include_directories(${EASYX_DIR}/include)
link_directories(${EASYX_DIR}/lib64)
link_libraries(libEasyX.a)

add_executable(wuziqi main.cpp
        ChessBoard.cpp
        Game.cpp
)
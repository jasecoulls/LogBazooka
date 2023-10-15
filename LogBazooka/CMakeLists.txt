# CMakeLists.txt for the LogBazooka project.

cmake_minimum_required(VERSION 3.0)
project(MyWin32Project CXX)

add_executable(LogBazooka LogBazooka.cpp LogRoutines.cpp HexDumper.cpp)

target_link_libraries(LogBazooka user32.lib)

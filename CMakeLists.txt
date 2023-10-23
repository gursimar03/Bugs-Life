cmake_minimum_required(VERSION 3.24)
project(bugslife)

set(CMAKE_CXX_STANDARD 14)

add_executable(bugslife
        main.cpp Bug.h Bug.cpp Crawler.h Crawler.cpp Hopper.h Hopper.cpp Board.h Board.cpp SuperBug.cpp SmartBug.h SmartBug.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(bugslife sfml-system sfml-window sfml-graphics sfml-audio)
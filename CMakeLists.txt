cmake_minimum_required(VERSION 3.27)
project(CA2_BugsLife_Michal_Becmer_D00256088)

set(CMAKE_CXX_STANDARD 17)

add_executable(CA2_BugsLife_Michal_Becmer_D00256088 main.cpp
        Bug.cpp
        Bug.h
        Direction.cpp
        Direction.h
        Board.cpp
        Board.h
        Hopper.cpp
        Hopper.h
        Crawler.cpp
        Crawler.h
        BattleAnt.cpp
        BattleAnt.h
)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML-2.6.1/include)
target_link_libraries(CA2_BugsLife_Michal_Becmer_D00256088 sfml-system sfml-window sfml-graphics sfml-audio)

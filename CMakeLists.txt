cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
project(SocGen)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks)

find_package(Imagine REQUIRED)

add_executable(SocGen
    Test1.cpp
    Pops.h        Pops.cpp
    Menu.h        Menu.cpp
    Symetriques.h Symetriques.cpp
    Rotation.h    Rotation.cpp
)

ImagineUseModules(SocGen Graphics)

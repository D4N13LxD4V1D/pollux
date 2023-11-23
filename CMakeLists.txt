cmake_minimum_required(VERSION 3.10)
project(Pollux VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(Pollux ${SOURCES})
target_include_directories(Pollux PRIVATE include)
target_compile_features(Pollux PRIVATE cxx_std_23)

install(TARGETS Pollux)
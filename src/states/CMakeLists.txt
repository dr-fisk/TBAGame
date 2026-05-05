cmake_minimum_required(VERSION 4.0)

project(LestGame)

target_include_directories(lestgame PRIVATE include)

target_sources(lestgame
  PRIVATE
    exceptionState.cpp
    mainMenuState.cpp
    sandboxState.cpp
    state.cpp

  PUBLIC
    FILE_SET include
    TYPE HEADERS
    BASE_DIRS
      ..
    FILES)

if(LINUX_BUILD)
target_compile_options(lestgame
  PRIVATE -g -O2 -std=c++17 -MMD -Wall -Wextra)
else()
target_link_options(lestgame PRIVATE
  -static-libgcc -static-libstdc++)

target_compile_options(lestgame
  PRIVATE -g -O2 -std=c++17 -MMD -Wall -Wextra -pthread)
endif()
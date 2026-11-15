cmake_minimum_required(VERSION 4.0)

target_include_directories(lestgame PRIVATE include)

target_sources(lestgame
  PRIVATE
    abstractButton.cpp
    button.cpp
    component.cpp
    componentManager.cpp
    frame.cpp
    graphics.cpp
    label.cpp
    menu.cpp
    menuItem.cpp
    modifier.cpp
    popupMenu.cpp
    scrollbar.cpp
    textbox.cpp
    textModifier.cpp
    toggleButton.cpp
    radioButton.cpp
    buttonGroup.cpp
  PUBLIC
    FILE_SET include
    TYPE HEADERS
    BASE_DIRS
      ../
    FILES
)

if(LINUX_BUILD)
target_compile_options(lestgame
  PRIVATE -g -O2 -std=c++17 -MMD -Wall -Wextra)
else()
target_link_options(lestgame PRIVATE
  -static-libgcc -static-libstdc++)
target_compile_options(lestgame
  PRIVATE -g -O2 -std=c++17 -MMD -Wall -Wextra -static-libstdc++)
endif()
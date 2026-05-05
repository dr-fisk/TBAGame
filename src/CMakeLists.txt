cmake_minimum_required(VERSION 4.0)

project(LestGame)

add_executable(lestgame main.cxx)

set(FontPath "${CMAKE_CURRENT_SOURCE_DIR}/../TtfFont")
set(ShaderPath "${CMAKE_CURRENT_SOURCE_DIR}/shaders")

target_include_directories(lestgame
  PRIVATE
    include
    include/lestttf)
add_subdirectory(states)
add_subdirectory(graphics)

add_custom_target(LestGameAssets
  "${FontPath}/Envy\ Code\ R.ttf"
  "${ShaderPath}/fragShader.txt"
  "${ShaderPath}/shader1.txt" )

add_custom_command(TARGET lestgame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:lestgame>/shaders)

add_custom_command(TARGET lestgame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${FontPath}/Envy\ Code\ R.ttf
        $<TARGET_FILE_DIR:lestgame>/)

target_sources(lestgame
  PRIVATE
    common.cpp
    game.cpp
  PUBLIC
    FILE_SET include
    TYPE HEADERS
    BASE_DIRS
      .
    FILES
      include/common.hpp
      include/exception.hpp
      include/game.hpp
      include/glcommon.hpp
      include/graphics/abstractButton.hpp
      include/graphics/actionListener.hpp
      include/graphics/button.hpp
      include/graphics/component.hpp
      include/graphics/componentManager.hpp
      include/graphics/frame.hpp
      include/graphics/itemListener.hpp
      include/graphics/label.hpp
      include/graphics/menu.hpp
      include/graphics/menuItem.hpp
      include/graphics/menuListener.hpp
      include/graphics/modifier.hpp
      include/graphics/popupMenu.hpp
      include/graphics/popupMenuListener.hpp
      include/graphics/scrollbar.hpp
      include/graphics/textModifier.hpp
      include/graphics/textbox.hpp
      include/graphics/toggleButton.hpp
      include/states/exceptionState.hpp
      include/states/mainMenuState.hpp
      include/states/sandboxState.hpp
      include/states/state.hpp
      include/lestttf/cmap.hpp
      include/lestttf/cvt.hpp
      include/lestttf/endianGeneral.hpp
      include/lestttf/fpgm.hpp
      include/lestttf/gasp.hpp
      include/lestttf/glyf.hpp
      include/lestttf/head.hpp
      include/lestttf/hhea.hpp
      include/lestttf/hmtx.hpp
      include/lestttf/kern.hpp
      include/lestttf/lestTableData.hpp
      include/lestttf/lestTtf.hpp
      include/lestttf/lestTtfData.hpp
      include/lestttf/loca.hpp
      include/lestttf/maxp.hpp
      include/lestttf/name.hpp
      include/lestttf/os2.hpp
      include/lestttf/post.hpp
      include/lestttf/prep.hpp
      include/lestttf/ttfTable.hpp
      include/lestttf/vdmx.hpp
      include/lestttf/vhea.hpp)

if(LINUX_BUILD)
target_compile_options(lestgame
  PRIVATE -g -O2 -std=c++17 -MMD -Wall -Wextra)
else()
set(LIBWIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

target_link_libraries(lestgame
  PRIVATE
    zlib1
    ws2_32
    "${LIBWIN_PATH}/libglfw3dll.a"
    "${LIBWIN_PATH}/libglew32.a"
    opengl32
    glu32
    gdi32
    "${LIBWIN_PATH}/lestmedia.dll"
    "${LIBWIN_PATH}/lestttf.dll"
    "${LIBWIN_PATH}/lestrenderengine.dll")

  add_custom_command(TARGET lestgame POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
          ${LIBWIN_PATH}/glfw3.dll
          $<TARGET_FILE_DIR:lestgame>/)

  add_custom_command(TARGET lestgame POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
          ${LIBWIN_PATH}/lestmedia.dll
          $<TARGET_FILE_DIR:lestgame>/)
  
  add_custom_command(TARGET lestgame POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
          ${LIBWIN_PATH}/lestttf.dll
          $<TARGET_FILE_DIR:lestgame>/)

  add_custom_command(TARGET lestgame POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
          ${LIBWIN_PATH}/lestrenderengine.dll
          $<TARGET_FILE_DIR:lestgame>/)

  add_custom_command(TARGET lestgame POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
          ${LIBWIN_PATH}/libwinpthread-1.dll
          $<TARGET_FILE_DIR:lestgame>/)

  add_custom_command(TARGET lestgame POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
          ${LIBWIN_PATH}/zlib1.dll
          $<TARGET_FILE_DIR:lestgame>/)

target_link_options(lestgame PRIVATE
  -static-libgcc -static-libstdc++)

target_compile_options(lestgame
  PRIVATE -g -O2 -std=c++17 -MMD -Wall -Wextra -pthread)
endif()
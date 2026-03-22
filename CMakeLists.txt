cmake_minimum_required(VERSION 3.15)

# мы любим древние хламовые маки (да и современные тоже)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7")
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)

if(LINUX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

project(logic-game)

add_executable(logic-game)

include_directories(${CMAKE_SOURCE_DIR}/include)

if(APPLE)
    set(BINNAME "macos")
    target_link_libraries(logic-game ${CMAKE_SOURCE_DIR}/lib/macos/libraylib.a "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(WIN32)
    # вин 7 форева
    set(BINNAME "win64")
    target_compile_definitions(logic-game PRIVATE _WIN32_WINNT=0x0601)
    if(MSVC)
        message(FATAL_ERROR Скачайте MSYS2)
    endif()
    target_link_libraries(logic-game ${CMAKE_SOURCE_DIR}/lib/win64/libraylib.a winmm)
elseif(LINUX)
    target_link_libraries(logic-game ${CMAKE_SOURCE_DIR}/lib/linux64/libraylib.a m X11)
    set(BINNAME "linux64")
endif()

set_target_properties(logic-game PROPERTIES OUTPUT_NAME "logic-${BINNAME}")

target_sources(logic-game PRIVATE src/main.c src/player.c)

cmake_minimum_required(VERSION 3.15)

# мы любим древние хламовые маки (да и современные тоже)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7")
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)

project(logic-game)

add_executable(logic-game)

include_directories(${CMAKE_SOURCE_DIR}/include)

if(APPLE)
    target_link_libraries(logic-game ${CMAKE_SOURCE_DIR}/lib/macos/libraylib.a "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(WIN32)
    # вин 7 форева
    target_compile_definitions(logic-game PRIVATE _WIN32_WINNT=0x0601)
    target_link_libraries(logic-game PRIVATE ${CMAKE_SOURCE_DIR}/lib/windows/raylib.lib)
elseif(LINUX)
### потом
endif()

target_sources(logic-game PRIVATE src/main.c src/player.c)

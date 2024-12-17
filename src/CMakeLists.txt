cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
project(Drodelyne VERSION 1.0.0)

add_executable(Game
               Board.cpp               
               Button.cpp
               Card.cpp
               DrawPile.cpp
               Events.cpp
               Image.cpp
               main.cpp
               Orchestra.cpp
               Player.cpp
               Rectangle.cpp
               Text.cpp
               UI.cpp
               Unit.cpp
               Window.cpp
               )

add_subdirectory(external/SDL-release-2.30.9)
add_subdirectory(external/SDL_image-release-2.8.2) # image manipulation
add_subdirectory(external/SDL_ttf-release-2.22.0) # font
add_subdirectory(external/SDL_mixer-release-2.8.0) # sound

target_link_libraries(Game PRIVATE 
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)

if (WIN32)
    target_link_libraries(
	Game PRIVATE SDL2main
    )
endif()

add_custom_command(
  TARGET Game POST_BUILD COMMAND
  ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:SDL2>
    $<TARGET_FILE:SDL2_image>
    $<TARGET_FILE:SDL2_ttf>
    $<TARGET_FILE:SDL2_mixer>
    $<TARGET_FILE_DIR:Game>
  VERBATIM 
)
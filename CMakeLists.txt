cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(galaga)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_Mixer REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(galaga Bullet.cpp CFG.cpp Core.cpp Elements.cpp Formations.cpp Game.cpp LevelsElement.cpp Music.cpp Objects.cpp Patterns.cpp Resources.cpp Rocket.cpp Ship.cpp StageM.cpp Text.cpp main.cpp physix.cpp shapes.cpp stages.cpp starsField.cpp texture.cpp timer.cpp)
target_link_libraries(galaga ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

install(TARGETS galaga DESTINATION bin)

set (source "${CMAKE_SOURCE_DIR}/resources")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/resources")

add_custom_command(
 TARGET ${PROJECT_NAME} POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
 DEPENDS ${destination}
 COMMENT "symbolic link resources folder from ${source} => ${destination}"
)

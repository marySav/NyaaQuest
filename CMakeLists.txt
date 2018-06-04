project(NyaaQuest)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules")

#find sfml
find_package(SFML 2.3.2 REQUIRED system window graphics network audio)



set(src main.cpp
  hero.cpp
  hero.h
  animation.cpp
  animation.h)

add_executable(NyaaQuest ${src})
target_link_libraries(NyaaQuest ${SFML_LIBRARIES})
set_target_properties(NyaaQuest PROPERTIES
  RESOURCE "/usr/share/fonts/truetype/tlwg/Purisa.ttf")

# select images and fonts
file(GLOB_RECURSE images images/*)
file(GLOB_RECURSE fonts "/usr/share/fonts/truetype/tlwg/Purisa.ttf")

#copy all resource files to the build directory
file(COPY ${images} DESTINATION images)
file(COPY ${fonts} DESTINATION fonts)

project(speedygrow)
cmake_minimum_required(VERSION 3.5)
set(SRC src/speedygrow.cpp src/circle.cpp src/gl.cpp src/world.cpp)
add_executable(speedygrow ${SRC})

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -std=c++11")

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES($ENV{HOME}/github/liquidfun/liquidfun/Box2D)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GLEW_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} $ENV{HOME}/github/liquidfun/liquidfun/Box2D/build/Box2D/Debug/libliquidfun.a)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION build)



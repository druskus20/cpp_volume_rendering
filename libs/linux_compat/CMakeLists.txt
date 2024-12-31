add_library(linux_compat INTERFACE            gl.h)
# Locate OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(linux_compat INTERFACE OpenGL::GL OpenGL::GLU X11)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/libs)
include_directories(${CMAKE_SOURCE_DIR}/lib)

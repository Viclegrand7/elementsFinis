cmake_minimum_required(VERSION 3.16)

project(meshReader)

find_package(VTK REQUIRED)

include_directories(".")

add_executable(meshReader
  main.cc
  mesh.cc
  triangle.cc)

set_target_properties(meshReader
  PROPERTIES
  COMPILE_FLAGS
  "-g -Wall -Werror -Wextra -Wshadow -Wunreachable-code -Wuninitialized -Wduplicated-cond -Wduplicated-branches -Wpedantic -Wno-unused-value -m64 -O3")

target_link_libraries(meshReader
  ${VTK_LIBRARIES})

install(TARGETS meshReader RUNTIME DESTINATION bin)
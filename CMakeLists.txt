cmake_minimum_required(VERSION 3.16)

project(meshReader)

find_package(VTK REQUIRED)

include_directories(".")

add_executable(meshReader
  main.cc
  mesh.cc
  triangle.cc)

add_executable(test1
  main_test.cc
  mesh.cc
  triangle.cc)

add_executable(test2
  main_test2.cc
  mesh.cc
  triangle.cc)

set_target_properties(meshReader
  PROPERTIES
  COMPILE_FLAGS
  "-g -Wall -Werror -Wextra -Wshadow -Wunreachable-code -Wuninitialized -Wpedantic -Wno-unused-parameter -m64 -O3")

set_target_properties(test1
  PROPERTIES
  COMPILE_FLAGS
  "-g -Wall -Werror -Wextra -Wshadow -Wunreachable-code -Wuninitialized -Wpedantic -Wno-unused-parameter -m64 -O3")

set_target_properties(test2
  PROPERTIES
  COMPILE_FLAGS
  "-g -Wall -Werror -Wextra -Wshadow -Wunreachable-code -Wuninitialized -Wpedantic -Wno-unused-parameter -m64 -O3")

install(TARGETS meshReader RUNTIME DESTINATION bin)

install(TARGETS test1 RUNTIME DESTINATION bin)

install(TARGETS test2 RUNTIME DESTINATION bin)
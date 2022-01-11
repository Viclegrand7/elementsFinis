cmake_minimum_required(VERSION 3.16)

project(meshReader)

include_directories(".")

add_executable(meshReader
  main.cc)

set_target_properties(meshReader
  PROPERTIES
  COMPILE_FLAGS
  "-g -Wall -Werror -Wextra -Wshadow -Wunreachable-code -Wuninitialized -Wduplicated-cond -Wduplicated-branches -Wpedantic -m64 -I /usr/include -O3")

install(TARGETS meshReader RUNTIME DESTINATION bin)
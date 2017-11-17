cmake_minimum_required(VERSION 2.6)

project(Tutorial)

set(MY_MAKEVAR 3.14)

configure_file(
  "${PROJECT_SOURCE_DIR}/generated.h.in"
  "${PROJECT_BINARY_DIR}/generated.h"
)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(Tutorial tutorial.cc)

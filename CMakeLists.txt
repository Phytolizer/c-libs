cmake_minimum_required(VERSION 3.23)

project(c-libs LANGUAGES C)

add_library("c-string" "src/c-string/lib.c")
target_include_directories("c-string" PUBLIC "include")

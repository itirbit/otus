cmake_minimum_required(VERSION 3.5)

project(06.allocator)

add_executable(allocator main.cpp reserveAllocator.h simpleContainer.h)
set_target_properties(allocator PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


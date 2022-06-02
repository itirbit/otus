cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(systemdesign VERSION ${PROJECT_VESRION})
configure_file(version.h.in version.h)

add_executable(exec main.cpp)
add_library(systemdesign lib.cpp)
set_target_properties(exec PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(systemdesign PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(exec PRIVATE systemdesign)
install(TARGETS exec RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(commandHandler VERSION ${PROJECT_VESRION})
configure_file(version.h.in version.h)

add_executable(bulk main.cpp)
add_library(commandHandler lib.cpp)
set_target_properties(bulk PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(commandHandler PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(bulk PRIVATE commandHandler)
install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
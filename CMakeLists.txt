cmake_minimum_required(VERSION 3.16)
project(mps_utils)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

enable_testing()
add_subdirectory(unit_tests)

add_library(${PROJECT_NAME} src/SvrDir.cpp include/SvrDir.h
        src/NotificationsAPI.cpp include/NotificationsAPI.h
        src/ParameterBuilder.cpp include/ParameterBuilder.h)

target_link_libraries(${PROJECT_NAME} my_utils curlpp curl)

#   INSTALL
if (UNIX AND NOT APPLE)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME})
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
endif ()
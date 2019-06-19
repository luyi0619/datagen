cmake_minimum_required(VERSION 3.2)
project(datagen)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wno-long-long -Wno-unused-variable -Wno-variadic-macros -pedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wno-long-long -Wno-unused-variable -Wno-variadic-macros -pedantic -O2")
set(CMAKE_CXX_STANDARD 14)

find_library(jemalloc_lib jemalloc) # jemalloc 5.0

# additional target to perform clang-format run, requires clang-format

# get all project files
file(GLOB_RECURSE ALL_SOURCE_FILES core/*.h common/*.h *-gen.cpp)

add_custom_target(
        format
        COMMAND clang-format
        -style=LLVM
        -i
        -sort-includes
        ${ALL_SOURCE_FILES}
)

add_executable(dense-gen dense-gen.cpp)
add_executable(sparse-gen sparse-gen.cpp)

if(APPLE)
    find_package(glog REQUIRED)
    find_package(gflags REQUIRED)
    target_link_libraries(dense-gen ${jemalloc_lib} glog::glog gflags)
    target_link_libraries(sparse-gen ${jemalloc_lib} glog::glog gflags)
else()
    target_link_libraries(dense-gen ${jemalloc_lib} glog gflags)
    target_link_libraries(sparse-gen ${jemalloc_lib} glog gflags)
endif()
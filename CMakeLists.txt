cmake_minimum_required(VERSION 3.10)
project(EasyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER g++)


set(SRC
    src/main.cpp
)
add_executable(${PROJECT_NAME} ${SRC})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -lpthread)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(EasyProject PRIVATE Threads::Threads)
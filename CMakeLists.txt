cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(DEFINED ENV{CXX})
  set(CMAKE_CXX_COMPILER $ENV{CXX})
else()
  find_program(CLANGXX clang++)

  if(CLANGXX)
    set(CMAKE_CXX_COMPILER ${CLANGXX})
  else()
    set(CMAKE_CXX_COMPILER "g++")
  endif()
endif()

project(dlopen_test CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")

option(COMPILE_COVERAGE "Compile with coverage flags enabled - default off" OFF)

if(COMPILE_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
  endif()
endif()

message(NOTICE "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}  | CMAKE_CXX_COMPILER_ID : ${CMAKE_CXX_COMPILER_ID}")

# sources
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SRCS main.cpp)

add_executable(${PROJECT_NAME} ${SRCS} ${FILE_SRCS})

add_library(plugin SHARED plugin.cpp)




#set(CMAKE_AUTOUIC_SEARCH_PATHS .)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
#qt_standard_project_setup()

#target_link_libraries(plugin sfml-graphics sfml-window sfml-system)
target_link_libraries(plugin Qt6::Widgets Qt6::Core Qt6::Gui)
target_compile_options(plugin PRIVATE "-fvisibility=hidden")
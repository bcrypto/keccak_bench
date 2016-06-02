cmake_minimum_required(VERSION 2.6)
project(KECCAK_BENCH C CXX)

option(WITH_AVX2 "Enable avx2 support." OFF)

set(CMAKE_BUILD_TYPE Release FORCE)


string(REGEX MATCH "Clang" CMAKE_COMPILER_IS_CLANG "${CMAKE_C_COMPILER_ID}")

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -W -Wdeclaration-after-statement -Wwrite-strings -Wlogical-op -Wno-parentheses -Wno-unused-parameter -Wno-strict-aliasing -O2")
  set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -W -Wdeclaration-after-statement -Wwrite-strings -Wlogical-op -Wno-parentheses -Wno-unused-parameter -Wno-strict-aliasing -O2")
  if(WITH_AVX2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -DAVX2")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx2 -DAVX2")
  endif(WITH_AVX2)
endif(CMAKE_COMPILER_IS_GNUCC)

if(CMAKE_COMPILER_IS_CLANG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -W -Wdeclaration-after-statement -Wwrite-strings -Wpointer-arith -Wno-parentheses -Wno-unused-parameter -Wno-strict-aliasing -O2")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -W -Wdeclaration-after-statement -Wwrite-strings -Wpointer-arith -Wno-parentheses -Wno-unused-parameter -Wno-strict-aliasing -O2")
  if(WITH_AVX2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=core-avx2 -DAVX2")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=core-avx2 -DAVX2")
  endif(WITH_AVX2)
endif(CMAKE_COMPILER_IS_CLANG)

if(CMAKE_COMPILER_IS_MSVC)
  # CMAKE_COMPILER_IS_MSVC is not automatically defined by cmake; defined it in command line
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /Ob2 /Ot")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2 /Ob2 /Ot")
  if(WITH_AVX2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /DAVX2")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:AVX2 /DAVX2")
  endif(WITH_AVX2)
endif(CMAKE_COMPILER_IS_MSVC)


#include_directories(include/)
include_directories(${BEE2_INCLUDE})
message(STATUS "bee2 include = " ${BEE2_INCLUDE})
link_directories(${BEE2_LIBS})
message(STATUS "bee2 libs = " ${BEE2_LIBS})

add_subdirectory(test)

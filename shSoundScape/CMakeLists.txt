cmake_minimum_required(VERSION 2.8.3)
project (shSoundScape)

if(APPLE)
  set(CS_LIB CsoundLib64)
else()
  set(CS_LIB csound64)
endif()

find_library(CS_LIB_PATH ${CS_LIB})
find_path(CSOUND_H_PATH csound.h)

message(HPATH: ${CSOUND_H_PATH})
message(LPATH: ${CS_LIB_PATH})

if(NOT CS_LIB_PATH)
    message(ERROR “Unable to find csound.h.”)
endif()


add_definitions(-DUSE_DOUBLE=1)
include_directories(${CSOUND_H_PATH})
include_directories(funcs.c)


function(make_example name src)
  add_executable(${name} ${src})
  target_link_libraries(${name} ${CS_LIB_PATH})
endfunction(make_example)

make_example(shSoundScape main.c)
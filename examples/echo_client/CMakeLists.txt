# ========================================
# Created by Lipson on 21-1-21.
# Email to LipsonChan@yahoo.com
# Copyright (c) 2021 Lipson. All rights reserved.
# version 1.0
# ========================================

string(REGEX REPLACE ".*/\(.*\)" "\\1" CURDIR ${CMAKE_CURRENT_SOURCE_DIR})
project(${CURDIR})

SET(CMAKE_C_STANDARD 11)

file(GLOB files *.cpp *.cc *.c *.h *.hpp)
add_executable(${PROJECT_NAME} ${files})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} uv_cpp uv)
target_include_directories(${PROJECT_NAME} PRIVATE ../..)
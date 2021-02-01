# ========================================
# Created by Lipson on 21-1-21.
# Email to LipsonChan@yahoo.com
# Copyright (c) 2021 Lipson. All rights reserved.
# version 1.0
# ========================================

SET(CMAKE_C_STANDARD 11)

FILE(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach (child ${children})
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child}
            AND (NOT ${child} STREQUAL ".git") AND (NOT ${child} STREQUAL ".idea")
            AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${child}/CMakeLists.txt)
        add_subdirectory(${child})
        message(STATUS "add example: ${child}")
    endif ()
endforeach ()

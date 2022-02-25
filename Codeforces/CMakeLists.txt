cmake_minimum_required(VERSION 3.10)
project(Codeforces)

set(CMAKE_CXX_STANDARD 14)

# Add all subdirectories
file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*_D*")
foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}")
        file(GLOB SUBDIR_SRCS
                RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}"
                "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}/*.c"
                "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}/*.cpp")
        foreach(SUBDIR_SRC ${SUBDIR_SRCS})
            get_filename_component(SRC_FILENAME ${SUBDIR_SRC} NAME_WE)
            set(TARGET_NAME "${SUBDIR}_${SRC_FILENAME}")
            message(STATUS ${TARGET_NAME})
            add_executable(${TARGET_NAME} ${SUBDIR}/${SUBDIR_SRC})
        endforeach()
    endif()
endforeach()

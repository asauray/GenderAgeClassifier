cmake_minimum_required(VERSION 3.8)
project(GenderClassifier)
set (CMAKE_CXX_STANDARD 11)

set(OPENCV_PATH "usr/local/Cellar/opencv/2.4.13.2")
set(OPENCV_PATH_HEADER "$(OPENCV_PATH)/include")
set(OPENCV_PATH_LIB "$(OPENCV_PATH)/lib")

include_directories("include")

include_directories($(OPENCV_PATH_HEADER))
link_directories($(OPENCV_PATH_LIB))

file(
        GLOB_RECURSE
        header_files
        include/*
)

file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable (
    classifier
    ${header_files}
    ${source_files}
)

target_link_libraries(
        classifier
        opencv_core.2.4.13
        opencv_contrib.2.4.13
        opencv_highgui.2.4.13
        opencv_imgproc.2.4.13
        opencv_objdetect.2.4.13
)
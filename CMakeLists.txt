cmake_minimum_required(VERSION 3.8)
project(GenderClassifier)
set (CMAKE_CXX_STANDARD 11)

set(OPENCV_PATH /usr/local/Cellar/opencv3/3.2.0)
set(OPENCV_PATH_HEADER /usr/local/Cellar/opencv3/3.2.0/include)
set(OPENCV_PATH_LIB /usr/local/Cellar/opencv3/3.2.0/lib)


include_directories(/usr/local/Cellar/opencv3/3.2.0/include)
link_directories(/usr/local/Cellar/opencv3/3.2.0/lib)

include_directories("include")

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
        opencv_core.3.2.0
        opencv_face.3.2.0
        opencv_highgui.3.2.0
        opencv_imgproc.3.2.0
        opencv_objdetect.3.2.0
        opencv_video.3.2.0
        opencv_videoio.3.2.0
        opencv_imgcodecs.3.2.0
)
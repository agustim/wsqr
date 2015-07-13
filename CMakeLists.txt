cmake_minimum_required (VERSION 2.6)
project (ZBARCV)

set(CMAKE_MODULE_PATH ${ZBARCV_SOURCE_DIR})
find_package (OpenCV)
find_package (ZBar0)


add_executable (wsqr main.cpp)
target_link_libraries (wsqr ${OpenCV_LIBRARIES} ${ZBAR_LIBRARIES})

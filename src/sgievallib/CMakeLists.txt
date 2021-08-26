include_directories(${SGI_ROOT}/include/sgievallib)

set(SOURCES 
    Rectangle2D.cpp
)

add_library(sgievallib ${SOURCES})

include_directories(${SGI_ROOT}/include/sgievallib)

set(SOURCES 
    Entity.cpp
)

add_library(sgievallib ${SOURCES})

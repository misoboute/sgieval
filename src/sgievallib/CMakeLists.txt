include_directories(${SGI_ROOT}/include/sgievallib)

set(SOURCES 
    Entity.cpp
    EntityGrid.cpp
)

add_library(sgievallib ${SOURCES})

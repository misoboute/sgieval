include_directories(${SGI_ROOT}/include)

set(SOURCES 
    main.cpp
)

add_executable(sgievalmain ${SOURCES})

target_link_libraries(sgievalmain sgievallib)

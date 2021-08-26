include_directories(${SGI_ROOT}/include/sgievallib)

set(SOURCES 
    main.cpp
)

add_executable(sgievallib_test ${SOURCES})

target_link_libraries(sgievallib_test
    Threads::Threads
    GTest::gtest
    GTest::gtest_main
)

gtest_add_tests(TARGET sgievallib_test)

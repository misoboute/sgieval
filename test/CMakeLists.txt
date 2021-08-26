find_package(GTest NO_MODULE REQUIRED)
find_package(Threads REQUIRED)

include(GoogleTest)

include_directories(${SGI_ROOT}/include)

add_definitions(-DGTEST_LANG_CXX11=1)

add_subdirectory(sgievallib)

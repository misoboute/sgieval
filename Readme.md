Thank you for reviewing this code.

A few notes about the project.

I have initialized a git repository inside the project root directory and made rather granular commits as I made progress with the tasks. This way, you could review the progression of the solution against time by looking at the commit history. To see an overview of the steps enter in a terminal:
```sh
$ cd sgieval
$ git log
```

The project build system is based on CMake 3.15, and the unit tests are created using Google Test framework, therefore CMake will need to find for the tests to build.

To build the project without tests, generate the project with:
```sh
$ cd sgieval
$ cmake -DENABLE_TESTING=false -B./build
```

To build the project with the tests, generate the project with:
```sh
$ cd sgieval
$ cmake -D-DGTest_DIR=/path/to/where/GTestConfig.cmake/is/located -B./build
```
or
```sh
$ cd sgieval
$ cmake -D-DCMAKE_PREFIX_PATH=/GoogleTest/framework/install/root -B./build
```

If the Google Test framework is installed to a defaul install prefix where CMake can find it, you can simply generate with:

```sh
$ cd sgieval
$ cmake -B./build
```

After generating the build system you can build all the targets:
```sh
$ cd sgieval
$ cmake --build ./build
```

Then you can run all the unit tests:
```sh
$ cd sgieval/build
$ ctest
```

Then, to run main executable:
```sh
$ cd sgieval
$ ./build/src/sgievalmain/sgievalmain ./data/entityblueprints.txt
```

I have tested the solution on Ubuntu 20.04 with CMake 3.16.3, GoogleTest framework 1.10, and clang 11 but I expect it work on other major platforms equally well as I have taken care to keep the code as platform dependent as possible.

Please feel free to contact me if you have questions. You can also take a look at my GitHub page [here](https://github.com/misoboute).

Thanks again
Ismail

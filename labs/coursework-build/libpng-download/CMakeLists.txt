cmake_minimum_required(VERSION 2.8.2)

project(libpng-download NONE)

include(ExternalProject)
ExternalProject_Add(libpng-download
                    GIT_REPOSITORY;https://github.com/glennrp/libpng.git;GIT_TAG;f981826
                    SOURCE_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/libpng-src"
                    BINARY_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/libpng-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

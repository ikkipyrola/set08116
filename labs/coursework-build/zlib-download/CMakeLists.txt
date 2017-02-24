cmake_minimum_required(VERSION 2.8.2)

project(zlib-download NONE)

include(ExternalProject)
ExternalProject_Add(zlib-download
                    GIT_REPOSITORY;https://github.com/madler/zlib;GIT_TAG;2fa463b
                    SOURCE_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/zlib-src"
                    BINARY_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/zlib-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

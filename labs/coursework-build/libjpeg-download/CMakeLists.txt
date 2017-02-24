cmake_minimum_required(VERSION 2.8.2)

project(libjpeg-download NONE)

include(ExternalProject)
ExternalProject_Add(libjpeg-download
                    GIT_REPOSITORY;https://github.com/dooglz/libjpeg.git;GIT_TAG;204c83c449
                    SOURCE_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/libjpeg-src"
                    BINARY_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/libjpeg-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

cmake_minimum_required(VERSION 2.8.2)

project(glew-download NONE)

include(ExternalProject)
ExternalProject_Add(glew-download
                    GIT_REPOSITORY;https://github.com/Perlmint/glew-cmake.git;GIT_TAG;7be0923
                    SOURCE_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/glew-src"
                    BINARY_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/glew-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

cmake_minimum_required(VERSION 2.8.2)

project(glfw-download NONE)

include(ExternalProject)
ExternalProject_Add(glfw-download
                    GIT_REPOSITORY;https://github.com/glfw/glfw.git;GIT_TAG;0f488ac
                    SOURCE_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/glfw-src"
                    BINARY_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/glfw-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

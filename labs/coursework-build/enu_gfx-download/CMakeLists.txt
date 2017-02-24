cmake_minimum_required(VERSION 2.8.2)

project(enu_gfx-download NONE)

include(ExternalProject)
ExternalProject_Add(enu_gfx-download
                    GIT_REPOSITORY;https://github.com/edinburgh-napier/set08116_framework;GIT_TAG;master
                    SOURCE_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/enu_gfx-src"
                    BINARY_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/enu_gfx-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

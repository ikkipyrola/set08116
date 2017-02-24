cmake_minimum_required(VERSION 2.8.2)

project(assimp-download NONE)

include(ExternalProject)
ExternalProject_Add(assimp-download
                    GIT_REPOSITORY;https://github.com/assimp/assimp;GIT_TAG;a8673d4
                    SOURCE_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src"
                    BINARY_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

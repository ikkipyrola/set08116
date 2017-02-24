cmake_minimum_required(VERSION 2.8.2)

project(glm-download NONE)

include(ExternalProject)
ExternalProject_Add(glm-download
                    GIT_REPOSITORY;https://github.com/g-truc/glm.git;GIT_TAG;6a1e2ec
                    SOURCE_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/glm-src"
                    BINARY_DIR          "C:/Users/40212722/Desktop/set08116/labs/coursework-build/glm-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

# Install script for directory: C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/set08116_graphics_coursework")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/40212722/Desktop/set08116/labs/coursework-build/bin/DEBUG/assimp.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/40212722/Desktop/set08116/labs/coursework-build/bin/RELEASE/assimp.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/40212722/Desktop/set08116/labs/coursework-build/bin/MINSIZEREL/assimp.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/40212722/Desktop/set08116/labs/coursework-build/bin/RELWITHDEBINFO/assimp.lib")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.3.1" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/40212722/Desktop/set08116/labs/coursework-build/bin/DEBUG/assimp.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/40212722/Desktop/set08116/labs/coursework-build/bin/RELEASE/assimp.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/40212722/Desktop/set08116/labs/coursework-build/bin/MINSIZEREL/assimp.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/40212722/Desktop/set08116/labs/coursework-build/bin/RELWITHDEBINFO/assimp.dll")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/anim.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/ai_assert.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/camera.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/color4.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/color4.inl"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/config.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/defs.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/cfileio.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/light.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/material.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/material.inl"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/matrix3x3.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/matrix3x3.inl"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/matrix4x4.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/matrix4x4.inl"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/mesh.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/postprocess.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/quaternion.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/quaternion.inl"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/scene.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/metadata.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/texture.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/types.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/vector2.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/vector2.inl"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/vector3.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/vector3.inl"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/version.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/cimport.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/importerdesc.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/Importer.hpp"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/DefaultLogger.hpp"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/ProgressHandler.hpp"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/IOStream.hpp"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/IOSystem.hpp"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/Logger.hpp"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/LogStream.hpp"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/NullLogger.hpp"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/cexport.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/Exporter.hpp"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/Compiler/poppack1.h"
    "C:/Users/40212722/Desktop/set08116/labs/coursework-build/assimp-src/code/../include/assimp/Compiler/pstdint.h"
    )
endif()


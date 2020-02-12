cmake_minimum_required(VERSION 3.1)

project(ucdavis-3D-electricity-map VERSION 1.0.0 LANGUAGES CXX)
set(EXENAME ucdavis-3D-electricity-map)

# Configurable Options
set(BUILD_SHARED_LIBS ON)
set(BUILD_STATIC_LIBS ON)

# Automatically compile .ui to .h
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QTDIR $ENV{QTDIR})

set(CMAKE_PREFIX_PATH ${QTDIR})
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules ${OGRE_HOME}/CMake/)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")

find_package(Qt5Widgets REQUIRED)

include_directories(
  third_party
  third_party/OCCT
  third_party/hjson/include

  "${PROJECT_SOURCE_DIR}/src"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

link_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/lib
)


# cmake hjson
add_subdirectory(third_party/hjson ${CMAKE_BINARY_DIR}/hjson)
add_subdirectory(src/plugins)

set(SOURCES ${SOURCES}
  src/UI/main.cpp
  src/UI/Application.cpp
  src/UI/MainWindow.cpp

  src/UI/Application.hpp
  src/UI/MainWindow.hpp
  src/UI/universalInclude.hpp
  src/core/config.hpp
)

set(RESOURCES ${RESOURCES}
  src/UI/main.ui
  resources/occqt.qrc
  resources/icons_utility.qrc
)

add_executable(${EXENAME} ${SOURCES} ${RESOURCES})

target_link_libraries(${EXENAME} PRIVATE
  # QT5
  Qt5::Widgets

  # HJSON for loading settings files
  hjson

  # flatbuffers
  flatbuffers

  # static link a bunch of stuff
  z
  windowscodecs
  stdc++
  gcc
  opengl32
  glu32
  gdi32
  comdlg32
  oleaut32
  imm32
  winmm
  winspool
  kernel32
  user32
  shell32
  uuid
  ole32
  advapi32
  ws2_32
  mingw32
  rpcrt4
  tiff
  # std::filesystem
  stdc++fs

  UCD_OSI_DataLib
  MapViewerOCCLib
  UCD3DEM_ManagerLib
)

target_include_directories(${EXENAME} PRIVATE
  third_party
  third_party/OCCT
  third_party/hjson/include
)

if(APPLE)
  find_library(COCOA_FRAMEWORK Cocoa)
  target_link_libraries(${EXENAME} ${COCOA_FRAMEWORK})
endif()

if(WIN32)
  set_target_properties(${EXENAME} PROPERTIES
    WIN32 TRUE
  )
elseif(APPLE)
  set_target_properties(${EXENAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    RESOURCE "${RESOURCES}"
  )
endif()

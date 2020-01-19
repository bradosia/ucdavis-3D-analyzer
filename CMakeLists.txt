cmake_minimum_required(VERSION 3.5)

project(ucdavis-3D-analyzer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXENAME ucdavis-3D-analyzer)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# configure compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
# generate proper GUI program on specified platform
if(WIN32) # Check if we are on Windows
        if(MINGW)
            # COMPILER-SETTINGS FOR MINGW
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=gnu++17")
            # SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
        elseif(MSVC) # Check if we are using the Visual Studio compiler
            set_target_properties(${PROJECT_NAME} PROPERTIES
                WIN32_EXECUTABLE YES
                LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
            # COMPILER-SETTINGS FOR MS VISUAL C++
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
            # To fix error: C2338: va_start argument must not
            # have reference type and must not be parenthesized
            add_definitions(/D_CRT_NO_VA_START_VALIDATION)
            add_definitions(/DNOMINMAX)
        else()
            message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
        endif(MSVC)
elseif(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                        MACOSX_BUNDLE YES
        )
elseif(UNIX)
        # Nothing special required
else()
        message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)


if(MINGW)
  # COMPILER-SETTINGS FOR MINGW
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")
elseif(MSVC)
  # COMPILER-SETTINGS FOR MS VISUAL C++
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
  # To fix error: C2338: va_start argument must not
  # have reference type and must not be parenthesized
  add_definitions(/D_CRT_NO_VA_START_VALIDATION)
  add_definitions(/DNOMINMAX)
endif()

 add_executable(${EXENAME}
    src/UCDavis3DAnalyzerUI/main.cpp
    src/UCDavis3DAnalyzerUI/mainwindow.cpp
    src/UCDavis3DAnalyzerUI/osisoft_pi_api.cpp
    src/UCDavis3DAnalyzerUI/view3DMap.cpp

    src/UCDavis3DAnalyzerUI/amalgamated.cpp
    src/UCDavis3DAnalyzerUI/occView.cpp
    src/UCDavis3DAnalyzerUI/aconf2.h
    src/UCDavis3DAnalyzerUI/aconf.h

    src/UCDavis3DAnalyzerUI/mainwindow.h
    include/UCDavis3DAnalyzer/amalgamated.h
    include/UCDavis3DAnalyzer/occView.h
    include/UCDavis3DAnalyzer/config.h
    include/UCDavis3DAnalyzer/osisoft_pi_api.h
    include/UCDavis3DAnalyzer/view3DMap.h

    src/UCDavis3DAnalyzerUI/occQt.ui
    resources/occqt.qrc
 )

target_link_directories(${EXENAME} PRIVATE
lib third_party/OGRE/lib)

target_link_libraries(${EXENAME} PRIVATE
# QT5
Qt5::Widgets

# OGRE
OgreMain

# 3D openCascade
TKSTEP
TKSTEPAttr
TKSTEP209
TKSTEPBase
TKXSBase
TKXCAF
TKOpenGl
TKV3d
TKService
TKCAF
TKOffset
TKFillet
TKBool
TKBO
TKShHealing
TKVCAF
TKMesh
TKHLR
TKPrim
TKTopAlgo
TKGeomAlgo
TKBRep
TKGeomBase
TKG3d
TKG2d
TKLCAF
TKCDF
TKernel
TKMath

# freetype
freetype
harfbuzz
gio-2.0
glib-2.0
intl
graphite2
libpng
bz2

# curl
curl
nghttp2
psl.dll
idn2
gnutls
ssl
crypto
cares
ssh2
brotlidec-static
brotlienc-static
brotlicommon-static
unistring
wldap32
libz
bcrypt
crypt32

# static link a bunch of stuff
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
)

target_include_directories(${EXENAME} PRIVATE
include
third_party
third_party/OCCT
third_party/aconf
third_party/OGRE/include
)

# Installation
install(TARGETS ${EXENAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

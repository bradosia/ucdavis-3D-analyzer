# UC Davis 3D Electricity Map
A visual 3D viewer for UC Davis electricity usage.

# Demo
![demo_photo-1](https://github.com/bradosia/ucdavis-3D-analyzer/blob/master/share/screen-shot-hart-hall.jpg?raw=true)

![demo_photo-2](https://github.com/bradosia/ucdavis-3D-analyzer/blob/master/share/screen-shot-main.jpg?raw=true)

![demo_photo-3](https://github.com/bradosia/ucdavis-3D-analyzer/blob/master/share/screen-shot-phone-app.jpg?raw=true)


# Build

## Dependencies
* QT5
  * Use package manager to install
* flatbuffers
  * Use package manager to install
* OpenCascade
  * https://github.com/tpaviot/oce/releases/tag/OCE-0.18.3
* HJson
  * Source included
  * compiled and static linked with cmake
* RapidJSON
  * Header only library so no binary installation required
* CURL
  * binary for MinGW64-gcc-9.2.0 included
  * static linked with all dependencies
  * NOTE: some of the included dependencies binaries are different than their package manager versions in order to maintain a full static link in this project

### Pacman 
NOT A COMPREHENSIVE LIST:
```shell
pacman -S mingw-w64-x86_64-qt5 mingw-w64-x86_64-flatbuffers mingw-w64-x86_64-curl
```

### Apt-get
NOT A COMPREHENSIVE LIST:
```shell
apt-get install qt5-default
```

### Nuget
NOT A COMPREHENSIVE LIST:
```shell
Install-Package Qt5BaseMsvc2017 -Version 5.9.3
```

## Cmake build
for MSYS2/MinGW
```shell
cmake -G "MSYS2 Makefiles -B build
cd build
make
```

# Licence 
LGPL


# UC Davis 3D Electricity Map
A visual 3D viewer for UC Davis electricity usage.

# Demo
![demo_photo-1](https://github.com/bradosia/ucdavis-3D-analyzer/blob/master/share/screen-shot-hart-hall.jpg?raw=true)

![demo_photo-2](https://github.com/bradosia/ucdavis-3D-analyzer/blob/master/share/screen-shot-main.jpg?raw=true)

![demo_photo-3](https://github.com/bradosia/ucdavis-3D-analyzer/blob/master/share/screen-shot-phone-app.jpg?raw=true)


# Build

## Dependencies

### Pacman 
```shell
pacman -S mingw-w64-x86_64-flatbuffers mingw-w64-x86_64-qt5 mingw-w64-x86_64-curl
```

## Cmake build
for MSYS2/MinGW
```shell
cmake -G "MSYS2 Makefiles -B build
cd build
make
```

# Libraries used
* QT5
* OpenCascade
* RapidJSON
* CURL

# Licence 
LGPL


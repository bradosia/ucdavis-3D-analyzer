/*
 * @name UC Davis 3D Analyzer
 * @author Brad Lee & SiYi Meng
 * @version 1.01
 * @license GNU LGPL v3
 * @brief 3D map of UC Davis electricity usage
 *
 * QT and OCC integration:
 * Copyright (c) 2018 Shing Liu (eryar@163.com)
 * License: MIT
 * Source: https://github.com/eryar/occQt
 *
 * Data from OSIsoft and UC Davis
 * Icons and images owned by their respective owners
 */

#ifndef UCD3DEM_MANAGER_UNIVERSAL_INCLUDE_H
#define UCD3DEM_MANAGER_UNIVERSAL_INCLUDE_H

// c++17
#include <algorithm> // std::find
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

// c
#define _USE_MATH_DEFINES // M_PI
#include <cmath>
#include <stdio.h>
#include <stdlib.h> /* srand, rand */
#include <string.h>

/* Flatbuffers 1.11.0-2
 * License: Apache License 2.0
 */
#include <flatbuffers/flatbuffers.h>

/* MapViewerOCC PLUGIN
 */
#include "../MapViewerOCC/MainWidget.hpp"

/* MapViewerOCC PLUGIN
 */
#include "../UCD_OSI_Data/MainWidget.hpp"

#endif // UCD3DEM_MANAGER_UNIVERSAL_INCLUDE_H

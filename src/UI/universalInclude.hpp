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

#ifndef UNIVERSAL_INCLUDE_H
#define UNIVERSAL_INCLUDE_H

// config
#include "../core/config.hpp"

// c++17
#include <algorithm> // std::find
#include <filesystem>
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

/* hjson-cpp 1.4
 * License: MIT
 */
#include <hjson/hjson.h>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QRubberBand>
#include <QString>
#include <QStyleFactory>
#include <QToolBar>
#include <QTranslator>
#include <QTreeView>
#include <QHBoxLayout>
#include <QObject>

/* Plugins
 * 2020-02-10: Plugins must be compiled with the same compiler as
 * the main application because there isn't a solution for
 * using a widget using only Plain Old Data (POD) Objects
 * with the shared library plugin to allow any compiler to
 * make a shared library plugin that has binary compatability
 * with the main application.
 * In the chance there may be some solution, plugins should
 * attempt to minimize passing non Plain Old Data (POD) Objects
 * directly and should communicate with flatbuffers
 */
#include <plugins/MapViewerOCC/MainWidget.hpp>
#include <plugins/UCD3DEM_Manager/MainWidget.hpp>
#include <plugins/UCD_OSI_Data/MainWidget.hpp>

#endif // UNIVERSAL_INCLUDE_H

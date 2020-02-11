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

#ifndef UCD_OSI_DATA_UNIVERSAL_INCLUDE_H
#define UCD_OSI_DATA_UNIVERSAL_INCLUDE_H

// c++17
//#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

// c
#include <stdio.h>
#include <stdlib.h> /* srand, rand */
#include <string.h>

/*
 * CURL 7.68.0
 * License: MIT/X inspired
 */
#define CURL_STATICLIB
#include <brotli/decode.h>
#include <curl/curl.h>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h> // rapidjson::ParseResult
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

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

#endif

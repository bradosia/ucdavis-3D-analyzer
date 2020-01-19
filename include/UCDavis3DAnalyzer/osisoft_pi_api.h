/*
 * Name        : PI WEB API for UC Davis
 * Author      : Brad Lee
 * Version     : 1.00
 * License     : GNU LGPL v3
 *
 */

#ifndef PWA_UCD_AMALGAMATED_H
#define PWA_UCD_AMALGAMATED_H

// c++17
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <fstream>

// c
#include <stdio.h>
#include <string.h>

/*
 * CURL 7.68.0
 * License: MIT/X inspired
 */
#define CURL_STATICLIB
#include <brotli/decode.h>
#include <curl/curl.h>

/* CURL EXE 7.68.0
 * Taken from the source from the CURL executable
 * EDIT 1: Code was taken out because source wouldn't static link
 */
//#include "curlx.h"
//#include "tool_setup.h"
//#include "tool_cfgable.h"
//#include "tool_msgs.h"
//#include "tool_doswin.h" // FindWin32CACert

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include "rapidjson/document.h"
#include "rapidjson/reader.h" // rapidjson::ParseResult
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/ostreamwrapper.h"

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QApplication>
#include <QFile>
#include <QTreeView>

/*
 * UCD3DA = UC Davis 3D Analyzer
 */
namespace UCD3DA {

/* Writes data from HTTP request into a string buffer
 * @param ptr data address
 */
size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s);
/* Makes an HTTPS GET request to the URI
 * @param URI The address
 */
rapidjson::Document HTTPS_GET_JSON(std::string URI);
void printJSON_value(const rapidjson::Value &a, unsigned int depth);
void printJSON_iterator(rapidjson::Value::ConstMemberIterator &itr,
                        unsigned int depth);
void getSettingsFile(std::string settingsFileString, std::string &inputURIString, std::string &outputFileString);

} // namespace PWA_UCD

// end PWA_UCD

#endif

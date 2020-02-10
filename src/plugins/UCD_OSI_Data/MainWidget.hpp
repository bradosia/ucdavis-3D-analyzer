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

#ifndef UCD_OSI_DATA_MAIN_WIDGET_H
#define UCD_OSI_DATA_MAIN_WIDGET_H

// Universal Include
#include "universalInclude.hpp"

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

class UCD_OSI_Data : public QWidget {
  Q_OBJECT

public:
  UCD_OSI_Data(QWidget *parent) {}
  ~UCD_OSI_Data(){};
};

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
void getSettingsFile(std::string settingsFileString,
                     std::string &inputURIString,
                     std::string &outputFileString);

} // namespace UCD3DEM

#endif
// end UCD_OSI_DATA_MAIN_WIDGET_H

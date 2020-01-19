/*
 * @name UC Davis 3D Analyzer
 * @author Brad Lee & SiYi Meng
 * @version 1.00
 * @license GNU LGPL v3
 * @brief 3D model analysis of UC Davis utility usage
 *
 * QT and OCC integration:
 * Copyright (c) 2018 Shing Liu (eryar@163.com)
 * License: MIT
 * Source: https://github.com/eryar/occQt
 *
 * Data from OSIsoft and UC Davis
 *
 * Icons and images owned by their respective owners
 */

#include "UCDavis3DAnalyzer/view3DMap.h"

/*
 * UCD3DA = UC Davis 3D Analyzer
 */
namespace UCD3DA {

void generateBuildings() {
  rapidjson::Document buildingInfo_JSON_Doc = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/tables/"
      "F1BlbgZy4oKQ9kiBiZJTW7eugwJhSOEaMUUUyOuVv2CDalxgVVRJTC1BRlxBQ0VcVEFCTEVT"
      "W0JVSUxESU5HX0RBVEFd/data");
  rapidjson::Document CAAN_JSON_Doc = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/tables/"
      "F1BlbgZy4oKQ9kiBiZJTW7eugwaKgvLoXhX0GjDFptjwvTcQVVRJTC1BRlxDRUZTXFRBQkxF"
      "U1tMQVRfTE9OR19EQVRBXQ/data");
  /*std::ofstream ofs("test.json");
    if ( !ofs.is_open() )
        {
       printf("ERROR: output file not found: %s\n","test.json");
          return ;
        }

         rapidjson::OStreamWrapper osw { ofs };
         rapidjson::PrettyWriter< rapidjson::OStreamWrapper> writer2 { osw };
        buildingInfo_JSON_Doc.Accept( writer2 );
        */
  std::unordered_map<std::string, coord> CAAN_table;
  if (CAAN_JSON_Doc.IsObject()) {
    if (CAAN_JSON_Doc.HasMember("Rows") && CAAN_JSON_Doc["Rows"].IsArray()) {
      const rapidjson::Value &a = CAAN_JSON_Doc["Rows"];
      rapidjson::SizeType n =
          a.Size(); // rapidjson uses SizeType instead of size_t.
      for (rapidjson::SizeType i = 0; i < n; i++) {
        if (a[i].IsObject()) {
          if (a[i].HasMember("CAAN Number") && a[i]["CAAN Number"].IsString()) {
            std::string CAAN_Number = a[i]["CAAN Number"].GetString();
            float latitude = std::stof(a[i]["Latitude"].GetString());
            float longitude = std::stof(a[i]["Longitude"].GetString());
            CAAN_table.insert({CAAN_Number, coord(latitude, longitude)});
            // printf("row CAAN: %s
            // (%f,%f)\n",CAAN_Number.c_str(),latitude,longitude);
          }
        }
      }
    }
  }

  std::vector<std::string> buildingCAANlist;
  if (buildingInfo_JSON_Doc.IsObject()) {
    if (buildingInfo_JSON_Doc.HasMember("Rows") &&
        buildingInfo_JSON_Doc["Rows"].IsArray()) {
      const rapidjson::Value &a = buildingInfo_JSON_Doc["Rows"];
      rapidjson::SizeType n =
          a.Size(); // rapidjson uses SizeType instead of size_t.
      for (rapidjson::SizeType i = 0; i < n; i++) {
        if (a[i].IsObject()) {
          if (a[i].HasMember("CAAN") && a[i]["CAAN"].IsString()) {
            buildingCAANlist.push_back(a[i]["CAAN"].GetString());
            // printf("row CAAN: %s\n",a[i]["CAAN"].GetString());
          }
        }
      }
    }
  }

  for (std::string buildingObj : buildingCAANlist) {
    if (CAAN_table.find(buildingObj) == CAAN_table.end()) {
      printf("HASH NOT FOUND: CAAN: %s\n", buildingObj.c_str());
    } else {
      coord &coordRef = CAAN_table.at(buildingObj);
      printf("HASH CAAN: %s (%f,%f)\n", buildingObj.c_str(), coordRef.latitude,
             coordRef.longitude);
    }
  }
}

} // namespace UCD3DA

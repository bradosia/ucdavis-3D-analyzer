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

#include "view3DMap.hpp"

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

void generateBuildings(std::shared_ptr<MapViewerOCC> myOccView) {
  // crashes, no time to debug
  std::thread thread(generateBuildingsTHREAD, myOccView);
  thread.detach();
  // generateBuildingsTHREAD(myOccView);
}

void exportDataserversPoints(QWidget *containerWidget) {
  QString fileName = QFileDialog::getSaveFileName(
      containerWidget, QObject::tr("Save JSON"), "",
      QObject::tr("JSON (*.json);;All Files (*)"));
  std::string outputFileString = fileName.toStdString();
  rapidjson::Document pointsJSON_Doc = HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/dataservers/"
      "F1DS9KoOKByvc0-uxyvoTV1UfQVVRJTC1QSS1Q/points");
  std::ofstream ofs(outputFileString.c_str());
  if (!ofs.is_open()) {
    printf("ERROR: output file not found: %s\n", outputFileString.c_str());
    return;
  }
  // write file
  rapidjson::OStreamWrapper osw{ofs};
  rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer2{osw};
  pointsJSON_Doc.Accept(writer2);
}

void unusedApiCalls() {
  // buildings with wifi data
  rapidjson::Document buildingsWithWifi = HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/elements/"
      "F1EmbgZy4oKQ9kiBiZJTW7eugwMLOlxFHu5hGUtUhRt5d2AAVVRJTC1BRlxBQ0VcVUMgREFW"
      "SVNcSUNTIEJVSUxESU5HUw/elements");

  // Click this link for an example response that shows the CAAN Value
  rapidjson::Document buildingCAAN = HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/attributes/"
      "F1AbEbgZy4oKQ9kiBiZJTW7eugwSTpv31Hu5hGUtUhRt5d2AAs4vVphFyDFs7-"
      "r25Y3ZvRQVVRJTC1BRlxBQ0VcVUMgREFWSVNcSUNTIEJVSUxESU5HU1xBQ0FEfEFTU0VUIE5"
      "VTUJFUg/value");

  // This is a URL that gives the link that will let you find the CAAN for the
  // building named “ACAD”
  rapidjson::Document findBuildingCAAN =
      HTTPS_GET_JSON("https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/"
                     "attributes?path=%20\\\\UTIL-AF\\ACE\\UC%20Davis\\ICS%"
                     "20Buildings\\ACAD|Asset%20Number");

  /*
   * To get the interpolated data for a WiFI reading for a specific building,
   * first contact itsattribute path and get the WebID, e.g for building “ACAD”,
   * go to this URL:
   */
  rapidjson::Document buildingWIFIinterpolated =
      HTTPS_GET_JSON("https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/"
                     "attributes?path=\\\\UTIL-AF\\ACE\\UC%20Davis\\ICS%"
                     "20Buildings\\ACAD|WIFI%20Occupants");

  /*
   * Use this Web ID along with Interpolated Data method of the Streams
   * controller, e.g.:
   */
  rapidjson::Document streamController = HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/streams/"
      "F1AbEbgZy4oKQ9kiBiZJTW7eugwSTpv31Hu5hGUtUhRt5d2AAfUAWf7mHRFMQvB3Pt0VKPgV"
      "VRJTC1BRlxBQ0VcVUMgREFWSVNcSUNTIEJVSUxESU5HU1xBQ0FEfFdJRkkgT0NDVVBBTlRT/"
      "interpolated");

  /*
   * You should pass in parameters for the start and end times of interests and
   * the desired interpolation interval, e.g. to get 1 hour of data for the year
   * of 2017:
   */
  rapidjson::Document interpolatedTimeInterval = HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/streams/"
      "F1AbEbgZy4oKQ9kiBiZJTW7eugwSTpv31Hu5hGUtUhRt5d2AAfUAWf7mHRFMQvB3Pt0VKPgV"
      "VRJTC1BRlxBQ0VcVUMgREFWSVNcSUNTIEJVSUxESU5HU1xBQ0FEfFdJRkkgT0NDVVBBTlRT/"
      "interpolated?starttime=2017&endtime=2018&interval=1h");

  rapidjson::Document kwh_cost = HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/tables/"
      "F1BlbgZy4oKQ9kiBiZJTW7eugwEttoGWANRE-ROARQB_"
      "54AgVVRJTC1BRlxVVElMSVRJRVNcVEFCTEVTW0tXSCBBTkQgVEhFUk0gQ09TVFNd/data");
}

void generateBuildingsTHREAD(std::shared_ptr<MapViewerOCC> myOccView) {
  rapidjson::Document buildingInfo_JSON_Doc = HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/tables/"
      "F1BlbgZy4oKQ9kiBiZJTW7eugwJhSOEaMUUUyOuVv2CDalxgVVRJTC1BRlxBQ0VcVEFCTEVT"
      "W0JVSUxESU5HX0RBVEFd/data");
  rapidjson::Document CAAN_JSON_Doc = HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/tables/"
      "F1BlbgZy4oKQ9kiBiZJTW7eugwaKgvLoXhX0GjDFptjwvTcQVVRJTC1BRlxDRUZTXFRBQkxF"
      "U1tMQVRfTE9OR19EQVRBXQ/data");

  std::unordered_map<std::string, coord> CAAN_table;
  CAAN_table.reserve(20000);
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
  buildingCAANlist.reserve(20000);
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
  srand(time(0));
  float epsilon = 0.00001;
  for (std::string buildingObj : buildingCAANlist) {
    if (CAAN_table.find(buildingObj) == CAAN_table.end()) {
      printf("HASH NOT FOUND: CAAN: %s\n", buildingObj.c_str());
    } else {
      coord &coordRef = CAAN_table.at(buildingObj);
      // decrease moves in X
      float lat_transform = (coordRef.latitude - 38.5311) * 55500;
      // increase moves in Y
      float lon_transform = (coordRef.longitude + 121.765) * 55500;
      // colors
      double randomDecimal = (double)rand() / RAND_MAX;
      double r, g, b, height;
      r = g = b = 0;
      height = randomDecimal * 20;

      if (lat_transform < 2000 && lat_transform > -2000 &&
          lon_transform > -2000 && lon_transform < 2000) {
        // color some markers for testing
        if (((coordRef.latitude < 38.53767461399 + epsilon &&
              coordRef.latitude > 38.53767461399 - epsilon) &&
             (coordRef.longitude < -121.748929568 + epsilon &&
              coordRef.longitude > -121.748929568 - epsilon))) {
          b = 1;
        } else if (((coordRef.latitude < 38.54258398621 + epsilon &&
                     coordRef.latitude > 38.54258398621 - epsilon) &&
                    (coordRef.longitude < -121.750213638 + epsilon &&
                     coordRef.longitude > -121.750213638 - epsilon))) {
          g = 1;
        } else {
          // need API call for electricity data, but same concept
          r = randomDecimal;
        }
        myOccView->addMarker(height, 3.0, r, g, b, lat_transform, lon_transform,
                             -8.0);
      }
#ifdef DEBUG_3D_GENERATION
      printf("MARKER: %s (%f,%f)->(%f,%f)\n", buildingObj.c_str(),
             coordRef.latitude, coordRef.longitude, lat_transform,
             lon_transform);
#endif
    }
  }
}

} // namespace UCD3DEM

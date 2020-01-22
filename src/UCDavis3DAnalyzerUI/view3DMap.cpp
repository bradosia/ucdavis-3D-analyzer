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

void generateMap(OccView *myOccView) {
  // create the shape
  TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(1000, 1000, 5.0).Shape();
  Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
  anAisBox->SetColor(Quantity_NOC_AZURE);

  // myOccView->getContext()->Display(anAisBox, Standard_True);
  // textured shape
  Handle(AIS_TexturedShape) aTShape = new AIS_TexturedShape(aTopoBox);
  TCollection_AsciiString aFile(
      "../ucdavis-3D-analyzer/resources/map_model/map/davis.png");
  aTShape->SetTextureFileName(aFile);
  aTShape->SetTextureMapOn();
  // int nRepeat = 1;
  double toScale = 1;
  // aTShape->SetTextureRepeat(Standard_True, nRepeat, nRepeat);
  aTShape->SetTextureRepeat(false, 1, 1);
  aTShape->SetTextureScale(Standard_True, toScale, toScale);
  aTShape->SetTextureOrigin(Standard_True, 0, 0);
  // aTShape->DisableTextureModulate();
  aTShape->SetDisplayMode(3); // mode 3 is "textured" mode
  aTShape->SetMaterial(Graphic3d_NOM_SILVER);
  // myOccView->getContext()->SetDisplayMode(aTShape, 3);
  // myOccView->getContext()->Display(aTShape, 3,-1);
  myOccView->getContext()->Display(aTShape, Standard_True);
  // myOccView->getContext()->Display(aTShape);
  myOccView->getContext()->UpdateCurrentViewer();
  aTShape->UpdateAttributes();
}
void generateBuildings(OccView *myOccView) {
  // crashes, no time to debug
  // std::thread thread(generateBuildingsTHREAD, myOccView);
  generateBuildingsTHREAD(myOccView);
}

void exportDataserversPoints(QMainWindow *mainWindow) {
  QString fileName =
      QFileDialog::getSaveFileName(mainWindow, QObject::tr("Save JSON"), "",
                                   QObject::tr("JSON (*.json);;All Files (*)"));
  std::string outputFileString = fileName.toStdString();
  rapidjson::Document pointsJSON_Doc = UCD3DA::HTTPS_GET_JSON(
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
  rapidjson::Document buildingsWithWifi = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/elements/"
      "F1EmbgZy4oKQ9kiBiZJTW7eugwMLOlxFHu5hGUtUhRt5d2AAVVRJTC1BRlxBQ0VcVUMgREFW"
      "SVNcSUNTIEJVSUxESU5HUw/elements");

  // Click this link for an example response that shows the CAAN Value
  rapidjson::Document buildingCAAN = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/attributes/"
      "F1AbEbgZy4oKQ9kiBiZJTW7eugwSTpv31Hu5hGUtUhRt5d2AAs4vVphFyDFs7-"
      "r25Y3ZvRQVVRJTC1BRlxBQ0VcVUMgREFWSVNcSUNTIEJVSUxESU5HU1xBQ0FEfEFTU0VUIE5"
      "VTUJFUg/value");

  // This is a URL that gives the link that will let you find the CAAN for the
  // building named “ACAD”
  rapidjson::Document findBuildingCAAN = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/"
      "attributes?path=%20\\\\UTIL-AF\\ACE\\UC%20Davis\\ICS%"
      "20Buildings\\ACAD|Asset%20Number");

  /*
   * To get the interpolated data for a WiFI reading for a specific building,
   * first contact itsattribute path and get the WebID, e.g for building “ACAD”,
   * go to this URL:
   */
  rapidjson::Document buildingWIFIinterpolated = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/"
      "attributes?path=\\\\UTIL-AF\\ACE\\UC%20Davis\\ICS%"
      "20Buildings\\ACAD|WIFI%20Occupants");

  /*
   * Use this Web ID along with Interpolated Data method of the Streams
   * controller, e.g.:
   */
  rapidjson::Document streamController = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/streams/"
      "F1AbEbgZy4oKQ9kiBiZJTW7eugwSTpv31Hu5hGUtUhRt5d2AAfUAWf7mHRFMQvB3Pt0VKPgV"
      "VRJTC1BRlxBQ0VcVUMgREFWSVNcSUNTIEJVSUxESU5HU1xBQ0FEfFdJRkkgT0NDVVBBTlRT/"
      "interpolated");

  /*
   * You should pass in parameters for the start and end times of interests and
   * the desired interpolation interval, e.g. to get 1 hour of data for the year
   * of 2017:
   */
  rapidjson::Document interpolatedTimeInterval = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/streams/"
      "F1AbEbgZy4oKQ9kiBiZJTW7eugwSTpv31Hu5hGUtUhRt5d2AAfUAWf7mHRFMQvB3Pt0VKPgV"
      "VRJTC1BRlxBQ0VcVUMgREFWSVNcSUNTIEJVSUxESU5HU1xBQ0FEfFdJRkkgT0NDVVBBTlRT/"
      "interpolated?starttime=2017&endtime=2018&interval=1h");

  rapidjson::Document kwh_cost = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/tables/"
      "F1BlbgZy4oKQ9kiBiZJTW7eugwEttoGWANRE-ROARQB_"
      "54AgVVRJTC1BRlxVVElMSVRJRVNcVEFCTEVTW0tXSCBBTkQgVEhFUk0gQ09TVFNd/data");
}

void generateBuildingsTHREAD(OccView *myOccView) {
  rapidjson::Document buildingInfo_JSON_Doc = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/tables/"
      "F1BlbgZy4oKQ9kiBiZJTW7eugwJhSOEaMUUUyOuVv2CDalxgVVRJTC1BRlxBQ0VcVEFCTEVT"
      "W0JVSUxESU5HX0RBVEFd/data");
  rapidjson::Document CAAN_JSON_Doc = UCD3DA::HTTPS_GET_JSON(
      "https://ucd-pi-iis.ou.ad3.ucdavis.edus/piwebapi/tables/"
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

      if (lat_transform < 2000 && lat_transform > -2000 &&
          lon_transform > -2000 && lon_transform < 2000) {
        gp_Ax2 anAxis;
        anAxis.SetLocation(gp_Pnt(lat_transform, lon_transform, -8.0));
        float r = (float)rand() / RAND_MAX;
        TopoDS_Shape aTopoReducer =
            BRepPrimAPI_MakeCone(anAxis, 3.0, 2.0, r * 20).Shape();
        Handle(AIS_Shape) anAisReducer = new AIS_Shape(aTopoReducer);
        // color some markers for testing
        if (((coordRef.latitude < 38.53767461399 + epsilon &&
              coordRef.latitude > 38.53767461399 - epsilon) &&
             (coordRef.longitude < -121.748929568 + epsilon &&
              coordRef.longitude > -121.748929568 - epsilon))) {
          anAisReducer->SetColor(
              Quantity_Color(0, 0, 1, Quantity_TypeOfColor::Quantity_TOC_RGB));
        } else if (((coordRef.latitude < 38.54258398621 + epsilon &&
                     coordRef.latitude > 38.54258398621 - epsilon) &&
                    (coordRef.longitude < -121.750213638 + epsilon &&
                     coordRef.longitude > -121.750213638 - epsilon))) {
          anAisReducer->SetColor(
              Quantity_Color(0, 1, 0, Quantity_TypeOfColor::Quantity_TOC_RGB));
        } else {
          // need API call for electricity data, but same concept
          anAisReducer->SetColor(
              Quantity_Color(r, 0, 0, Quantity_TypeOfColor::Quantity_TOC_RGB));
        }
        myOccView->getContext()->Display(anAisReducer, Standard_True);
      }
#ifdef DEBUG_3D_GENERATION
      printf("MARKER: %s (%f,%f)->(%f,%f)\n", buildingObj.c_str(),
             coordRef.latitude, coordRef.longitude, lat_transform,
             lon_transform);
#endif
    }
  }
}

} // namespace UCD3DA

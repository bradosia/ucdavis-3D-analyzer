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
  TCollection_AsciiString aFile("../ucdavis-3D-analyzer/resources/map_model/map/davis.png");
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

void generateBuildingsTHREAD(OccView *myOccView) {
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
  float epsilon = 0.00001;
  for (std::string buildingObj : buildingCAANlist) {
    if (CAAN_table.find(buildingObj) == CAAN_table.end()) {
      printf("HASH NOT FOUND: CAAN: %s\n", buildingObj.c_str());
    } else {
      coord &coordRef = CAAN_table.at(buildingObj);
      // decrease moves in X
      float lat_transform = (coordRef.latitude - 38.505) * 20000;
      // increase moves in Y
      float lon_transform = (coordRef.longitude + 121.781) * 20000;

      if (lat_transform < 2000 && lat_transform > -2000 &&
          lon_transform > -2000 && lon_transform < 2000) {
        gp_Ax2 anAxis;
        anAxis.SetLocation(gp_Pnt(lat_transform, lon_transform, -8.0));
        TopoDS_Shape aTopoReducer =
            BRepPrimAPI_MakeCone(anAxis, 1.0, 0.5, 5.0).Shape();
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
          anAisReducer->SetColor(
              Quantity_Color(1, 0, 0, Quantity_TypeOfColor::Quantity_TOC_RGB));
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

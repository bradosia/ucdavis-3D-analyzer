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

#ifndef VIEW_3D_MAP_H
#define VIEW_3D_MAP_H

// Universal Include
#include "universalInclude.hpp"

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

class coord {
public:
  coord(float lat, float lon) : latitude(lat), longitude(lon) {}
  float latitude;
  float longitude;
};

void generateMap(std::shared_ptr<MapViewerOCC> myOccView);
void generateBuildings(std::shared_ptr<MapViewerOCC> myOccView);
void exportDataserversPoints(QWidget *containerWidget);
void unusedApiCalls();
void generateBuildingsTHREAD(std::shared_ptr<MapViewerOCC> myOccView);

} // namespace UCD3DA

#endif // end VIEW_3D_MAP_H

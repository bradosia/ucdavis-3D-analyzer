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

#ifndef UCD3DEM_MANAGER_MAIN_WIDGET_H
#define UCD3DEM_MANAGER_MAIN_WIDGET_H

// Universal Include
#include "universalInclude.hpp"

#include "view3DMap.hpp"

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

class UCD3DEM_Manager : public QWidget {
  Q_OBJECT

public:
  UCD3DEM_Manager(QWidget *parent = nullptr){};
  ~UCD3DEM_Manager(){};

  // Set Up Oriented Methods
  void setDataWidget(std::shared_ptr<UCD_OSI_Data> widgetPtr_) {
    UCD_OSI_DataWidget = widgetPtr_;
  }
  void setViewerWidget(std::shared_ptr<MapViewerOCC> widgetPtr_) {
    MapViewerOCC_Widget = widgetPtr_;
  }
  void init();
  void MapViewerCallback(void);

  // UI elements
  void UI_OpenFile();
  void UI_About();

  // Map Viewer Interaction
  void mapZoom();
  void mapReset();
  void mapFitAll();
  void mapInputModeSelect();
  void mapInputModePan();
  void mapInputModeRotate();

  // Data
  void getServerDataAll();
  void dumpDataAll();

  // Heavy lifting
  void placeBuildings();
  void energyUsage();

private:
  // widgets
  std::shared_ptr<UCD_OSI_Data> UCD_OSI_DataWidget;
  std::shared_ptr<MapViewerOCC> MapViewerOCC_Widget;
};

} // namespace UCD3DEM

#endif // UCD3DEM_MANAGER_MAIN_WIDGET

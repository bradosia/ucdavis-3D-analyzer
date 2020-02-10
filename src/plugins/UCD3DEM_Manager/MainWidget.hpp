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

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

class UCD3DEM_Manager : public QWidget {
  Q_OBJECT

public:
  UCD3DEM_Manager(QWidget *parent = nullptr){};
  ~UCD3DEM_Manager(){};

  void setDataWidget(std::shared_ptr<UCD_OSI_Data> widgetPtr_) {
    UCD_OSI_DataWidget = widgetPtr_;
  }
  void setViewerWidget(std::shared_ptr<MapViewerOCC> widgetPtr_) {
    MapViewerOCC_Widget = widgetPtr_;
  }

protected:
  //! make cylindrical helix.
  void makeCylindricalHelix(void);

  //! make conical helix.
  void makeConicalHelix(void);

  //! make toroidal helix.
  void makeToroidalHelix(void);

private:
  // widgets
  std::shared_ptr<UCD_OSI_Data> UCD_OSI_DataWidget;
  std::shared_ptr<MapViewerOCC> MapViewerOCC_Widget;

private slots:
  void on_actionOpen_triggered();

  void on_actionAbout_triggered();

  void on_actionHelix_triggered();

  void on_actionSphere_triggered();

  void on_actionZoom_triggered();

  void on_actionPan_triggered();

  void on_actionRotate_triggered();

  void on_actionReset_triggered();

  void on_actionFitAll_triggered();

  void on_actionBox_triggered();

  void on_actionCone_triggered();

  void on_actionCylinder_triggered();

  void on_actionRevolve_triggered();

  void on_actionLoft_triggered();

  void on_actionCut_triggered();

  void on_actionFuse_triggered();

  void on_actionCommon_triggered();

  void on_actionTorus_triggered();

  void on_actionFillet_triggered();

  void on_actionChamfer_triggered();

  void on_actionExtrude_triggered();

  void on_actionSelect_triggered();

  void on_actionPlace_Buildings_triggered();

  void on_actionEnergyUsage_triggered();

  void on_actionData_Server_Points_triggered();

private:
};

} // namespace UCD3DEM

#endif // UCD3DEM_MANAGER_MAIN_WIDGET

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

#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  /* UI Setup
   */
  ui.setupUi(this);
  /* Plugins
   */
  // why does setObjectName() not seem to change the name
  this->setObjectName("testName");
  UCD_OSI_DataWidget = std::make_shared<UCD3DEM::UCD_OSI_Data>(this);
  MapViewerOCC_Widget = std::make_shared<UCD3DEM::MapViewerOCC>(this);
  UCD3DEM_ManagerWidget = std::make_unique<UCD3DEM::UCD3DEM_Manager>(this);
  // set up the manager
  UCD3DEM_ManagerWidget->setDataWidget(UCD_OSI_DataWidget);
  UCD3DEM_ManagerWidget->setViewerWidget(MapViewerOCC_Widget);

  /* find the layout in the centralWidget
   * add the plugin widgets to the layout
   */
  printf("===== DEBUG: ATTEMPTING TO FIND CENTRAL... =====\n");
  QList<QHBoxLayout *> widgetCentralWidgetList =
      this->findChildren<QHBoxLayout *>("horizontalLayout",
                                        Qt::FindChildrenRecursively);
  if (!widgetCentralWidgetList.empty()) {
    printf("===== DEBUG: CENTRAL FOUND =====\n");
    QHBoxLayout *layout = widgetCentralWidgetList.at(0);
    layout->addWidget(MapViewerOCC_Widget.get());
  }

  // initialize the map
  UCD3DEM_ManagerWidget->init();
}


void MainWindow::on_actionOpen_triggered() {
    UCD3DEM_ManagerWidget->UI_About();
}
void MainWindow::on_actionAbout_triggered() {
  UCD3DEM_ManagerWidget->UI_About();
}

// Toolbar
void MainWindow::on_actionZoom_triggered() { UCD3DEM_ManagerWidget->mapZoom(); }
void MainWindow::on_actionSelect_triggered() {
  UCD3DEM_ManagerWidget->mapInputModeSelect();
}
void MainWindow::on_actionPan_triggered() {
  UCD3DEM_ManagerWidget->mapInputModePan();
}
void MainWindow::on_actionRotate_triggered() {
  UCD3DEM_ManagerWidget->mapInputModeRotate();
}
void MainWindow::on_actionReset_triggered() {
  UCD3DEM_ManagerWidget->mapReset();
}
void MainWindow::on_actionFitAll_triggered() {
  UCD3DEM_ManagerWidget->mapFitAll();
}

// Test shape placing
void MainWindow::on_actionHelix_triggered() {}
void MainWindow::on_actionSphere_triggered() {}
void MainWindow::on_actionBox_triggered() {}
void MainWindow::on_actionCone_triggered() {}
void MainWindow::on_actionCylinder_triggered() {}
void MainWindow::on_actionRevolve_triggered() {}
void MainWindow::on_actionLoft_triggered() {}
void MainWindow::on_actionCut_triggered() {}
void MainWindow::on_actionFuse_triggered() {}
void MainWindow::on_actionCommon_triggered() {}
void MainWindow::on_actionTorus_triggered() {}
void MainWindow::on_actionFillet_triggered() {}
void MainWindow::on_actionChamfer_triggered() {}
void MainWindow::on_actionExtrude_triggered() {}

void MainWindow::on_actionPlace_Buildings_triggered() {
  UCD3DEM_ManagerWidget->placeBuildings();
}

void MainWindow::on_actionEnergyUsage_triggered() {
  UCD3DEM_ManagerWidget->placeBuildings();
}

void MainWindow::on_actionData_Server_Points_triggered() {}

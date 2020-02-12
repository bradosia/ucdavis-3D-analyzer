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

/*
 * UI
 */
#include "MainWidget.hpp"

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

void UCD3DEM_Manager::init() {
  MapViewerOCC_Widget->setInitCallback(
      std::bind(&UCD3DEM_Manager::MapViewerCallback, this));
}

void UCD3DEM_Manager::MapViewerCallback(void) {
  MapViewerOCC_Widget->generateMap();
  // flip rotation because of weird texture inversion
  // UCD3DA::generateMap(this);
  MapViewerOCC_Widget->viewRotate(270, 90, 180, 0, 0, 0);
  MapViewerOCC_Widget->fitAll();
}

void UCD3DEM_Manager::UI_OpenFile() {
  std::string inputFileString, exportSTEP_NameString;

  QString inputFileQString = QFileDialog::getOpenFileName(
      this, tr("Open Protein Model"), "C:\\github\\protein-knot-analyzer\\UI",
      tr("Protein Model Files (*.pdb *.cif *.bin *.crd)"));
  inputFileString = inputFileQString.toStdString();

  printf("Input File Set: %s\n", inputFileString.c_str());
  if (inputFileString.empty()) {
    printf("FATAL ERROR: No input file set.\n");
    return;
  }
}

void UCD3DEM_Manager::UI_About() {
  QMessageBox::about(
      this, tr("About UC Davis 3D Analyzer"),
      tr("<h2>UC Davis 3D Analyzer 1.0</h2><p>Author: Brad Lee & SiYi "
         "Meng</p><p>Framework of QT5 and OCC:"
         "Copyright &copy; 2014 eryar@163.com</p>"
         "<p>Icons made by <a "
         "href=\"https://www.flaticon.com/authors/pixel-perfect\" "
         "title=\"Pixel perfect\">Pixel perfect</a> from <a "
         "href=\"https://www.flaticon.com/\" title=\"Flaticon\"> "
         "www.flaticon.com</a></p>"));
}

void UCD3DEM_Manager::mapZoom() { MapViewerOCC_Widget->zoom(); }

void UCD3DEM_Manager::mapReset() { MapViewerOCC_Widget->reset(); }

void UCD3DEM_Manager::mapFitAll() { MapViewerOCC_Widget->fitAll(); }

void UCD3DEM_Manager::mapInputModeSelect() { MapViewerOCC_Widget->select(); }

void UCD3DEM_Manager::mapInputModePan() { MapViewerOCC_Widget->pan(); }

void UCD3DEM_Manager::mapInputModeRotate() { MapViewerOCC_Widget->rotate(); }

void UCD3DEM_Manager::getServerDataAll() {
  // get
}

void UCD3DEM_Manager::dumpDataAll() { exportDataserversPoints(this); }

void UCD3DEM_Manager::placeBuildings() {
  generateBuildings(MapViewerOCC_Widget);
}

void UCD3DEM_Manager::energyUsage() { generateBuildings(MapViewerOCC_Widget); }

} // namespace UCD3DEM

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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * Configuration
 */
#include <UCDavis3DAnalyzer/config.h>

// c++
#include <algorithm> // std::find
#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

/* UC Davis 3D Analyzer 1.00
 * 3D model analysis of UC Davis utility usage
 */
#include "UCDavis3DAnalyzer/amalgamated.h"
#include "UCDavis3DAnalyzer/occView.h"

/*
 * UI
 */
//#include "./ui_mainwindow.h"
#include "./ui_occQt.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

protected:
  //! make cylindrical helix.
  void makeCylindricalHelix(void);

  //! make conical helix.
  void makeConicalHelix(void);

  //! make toroidal helix.
  void makeToroidalHelix(void);

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

private:
  // Ui::MainWindow *ui;
  Ui::occQtClass *ui;

  // wrapped the widget for occ.
  OccView *myOccView;
};
#endif // MAINWINDOW_H

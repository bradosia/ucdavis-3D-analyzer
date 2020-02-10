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

#ifndef APPLICATION_H
#define APPLICATION_H

// c++
#include <memory>

// QT
#include <QApplication>

// MainWindow
#include "MainWindow.hpp"

class Application final : public QApplication {
public:
  Application(int &argc, char **argv);
  ~Application();

private:
  std::unique_ptr<MainWindow> mainWindow;
};

#endif // APPLICATION_H

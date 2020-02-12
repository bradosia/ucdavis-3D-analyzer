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
 *    Copyright (c) 2018 Shing Liu All Rights Reserved.
 *
 *           File : OccView.h
 *         Author : Shing Liu(eryar@163.com)
 *           Date : 2018-01-09 21:00
 *        Version : OpenCASCADE7.2.0 & Qt5.7.1
 *
 *    Description : Adapte OpenCASCADE view for Qt.
 */

#ifndef MAP_VIEWER_OCC_H
#define MAP_VIEWER_OCC_H

// Universal Include
#include "universalInclude.hpp"

#include "Shapes.hpp"

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

//! adapted a QOpenGLWidget for OpenCASCADE viewer.
class MapViewerOCC : public QWidget {
  Q_OBJECT

public:
  //! mouse actions.
  enum CurrentAction3d {
    CurAction3d_Nothing,
    CurAction3d_DynamicZooming,
    CurAction3d_WindowZooming,
    CurAction3d_DynamicPanning,
    CurAction3d_GlobalPanning,
    CurAction3d_DynamicRotation
  };

  enum mouse_button_left {
    mouse_button_left_select,
    mouse_button_left_rotate,
    mouse_button_left_pan
  };

  //! constructor.
  MapViewerOCC(QWidget *parent);
  ~MapViewerOCC();

  const Handle(AIS_InteractiveContext) & getContext() const;

  // Callbacks
  void setInitCallback(std::function<void(void)> cb_);

  // interface
  template <typename... Args> void viewRotate(Args... args) {
    myView->Rotate(args...);
  }
  void addMarker(double height, double radius, double r, double g, double b,
                 double x, double y, double z);
  void generateMap();

signals:
  void selectionChanged(void);

public slots:
  // operations for the view.
  void select(void);
  void pan(void);
  void fitAll(void);
  void reset(void);
  void zoom(void);
  void rotate(void);

protected:
  // Paint events.
  virtual void paintEvent(QPaintEvent *theEvent);
  virtual void resizeEvent(QResizeEvent *theEvent);

  // Mouse events.
  virtual void mousePressEvent(QMouseEvent *theEvent);
  virtual void mouseReleaseEvent(QMouseEvent *theEvent);
  virtual void mouseMoveEvent(QMouseEvent *theEvent);
  virtual void wheelEvent(QWheelEvent *theEvent);

  // Button events.
  virtual void onLButtonDown(const int theFlags, const QPoint thePoint);
  virtual void onMButtonDown(const int theFlags, const QPoint thePoint);
  virtual void onRButtonDown(const int theFlags, const QPoint thePoint);
  virtual void onMouseWheel(const int theFlags, const int theDelta,
                            const QPoint thePoint);
  virtual void onLButtonUp(const int theFlags, const QPoint thePoint);
  virtual void onMButtonUp(const int theFlags, const QPoint thePoint);
  virtual void onRButtonUp(const int theFlags, const QPoint thePoint);
  virtual void onMouseMove(const int theFlags, const QPoint thePoint);

  // Popup menu.
  virtual void addItemInPopup(QMenu *theMenu);

  void init(void);
  void popup(const int x, const int y);
  void dragEvent(const int x, const int y);
  void inputEvent(const int x, const int y);
  void moveEvent(const int x, const int y);
  void multiMoveEvent(const int x, const int y);
  void multiDragEvent(const int x, const int y);
  void multiInputEvent(const int x, const int y);
  void drawRubberBand(const int minX, const int minY, const int maxX,
                      const int maxY);
  void panByMiddleButton(const QPoint &thePoint);

private:
  // Callbacks
  std::function<void(void)> initCallback;

  // handles
  opencascade::handle<V3d_Viewer> myViewer;
  opencascade::handle<V3d_View> myView;
  opencascade::handle<AIS_InteractiveContext> myContext;

  // save the mouse position.
  int myXmin;
  int myYmin;
  int myXmax;
  int myYmax;

  // the mouse current mode.
  CurrentAction3d myCurrentMode;
  mouse_button_left mouseButtonLeftMode;

  // save the degenerate mode state.
  Standard_Boolean myDegenerateModeIsOn;

  // rubber rectangle for the mouse selection.
  QRubberBand *myRectBand;
  QOpenGLContext *mOpenGLContext;
};

} // namespace UCD3DEM

#endif // OCC_VIEW_H

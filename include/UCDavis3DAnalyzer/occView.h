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

#ifndef OCC_VIEW_H
#define OCC_VIEW_H

/* proteinKnotAnalyzer 1.00
 * Analysis utilities for PDB format support and
 * STEP file export for visualization
 */
#include "UCDavis3DAnalyzer/amalgamated.h"

//! adapted a QOpenGLWidget for OpenCASCADE viewer.
class OccView : public QOpenGLWidget {
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

public:
  //! constructor.
  OccView(QWidget *parent);
  ~OccView();

  const Handle(AIS_InteractiveContext) & getContext() const;

signals:
  void selectionChanged(void);

public slots:
  //! operations for the view.
  void select(void);
  void pan(void);
  void fitAll(void);
  void reset(void);
  void zoom(void);
  void rotate(void);

protected:
  void initializeGL();

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

protected:
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
  //! the occ viewer.
  Handle(V3d_Viewer) myViewer;

  //! the occ view.
  Handle(V3d_View) myView;

  //! the occ context.
  Handle(AIS_InteractiveContext) myContext;

  //! save the mouse position.
  Standard_Integer myXmin;
  Standard_Integer myYmin;
  Standard_Integer myXmax;
  Standard_Integer myYmax;

  //! the mouse current mode.
  CurrentAction3d myCurrentMode;
  mouse_button_left mouseButtonLeftMode;

  //! save the degenerate mode state.
  Standard_Boolean myDegenerateModeIsOn;

  //! rubber rectangle for the mouse selection.
  QRubberBand *myRectBand;
  QOpenGLContext *mOpenGLContext;
};

#endif // OCC_VIEW_H

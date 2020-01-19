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

#include "UCDavis3DAnalyzer/occView.h"

static Handle(Graphic3d_GraphicDriver) & GetGraphicDriver() {
  static Handle(Graphic3d_GraphicDriver) aGraphicDriver;
  return aGraphicDriver;
}

OccView::OccView(QWidget *parent)
    : QOpenGLWidget(parent), myXmin(0), myYmin(0), myXmax(0), myYmax(0),
      myCurrentMode(CurAction3d_DynamicRotation),
      myDegenerateModeIsOn(Standard_True), myRectBand(nullptr) {
  mouseButtonLeftMode = mouse_button_left_select;
  // No Background
  setBackgroundRole(QPalette::NoRole);

  // Enable the mouse tracking, by default the mouse tracking is disabled.
  setMouseTracking(true);

  // mOpenGLContext = new QOpenGLContext(this);
  // QSurfaceFormat format = requestedFormat();
  // mOpenGLContext->setScreen(this->screen);
  // mOpenGLContext->create();
}

void OccView::init() {
  // Create Aspect_DisplayConnection
  Handle(Aspect_DisplayConnection) aDisplayConnection =
      new Aspect_DisplayConnection();

  // Get graphic driver if it exists, otherwise initialise it
  if (GetGraphicDriver().IsNull()) {
    GetGraphicDriver() = new OpenGl_GraphicDriver(aDisplayConnection);
  }

  // Get window handle. This returns something suitable for all platforms.
  WId window_handle = static_cast<WId>(winId());

// Create appropriate window for platform
#ifdef WIN32
  Handle(WNT_Window) wind =
      new WNT_Window(reinterpret_cast<Aspect_Handle>(window_handle));
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
  Handle(Cocoa_Window) wind = new Cocoa_Window((NSView *)window_handle);
#else
  Handle(Xw_Window) wind =
      new Xw_Window(aDisplayConnection, (Window)window_handle);
#endif

  // Create V3dViewer and V3d_View
  myViewer =
      new V3d_Viewer(GetGraphicDriver() /*, Standard_ExtString("viewer3d")*/);

  myView = myViewer->CreateView();

  myView->SetWindow(wind);
  if (!wind->IsMapped())
    wind->Map();

  // Create AISInteractiveContext
  myContext = new AIS_InteractiveContext(myViewer);

  // Set up lights etc
  myViewer->SetDefaultLights();
  myViewer->SetLightOn();

  myView->SetBackgroundColor(Quantity_NOC_BLACK);
  myView->MustBeResized();
  myView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08,
                          V3d_ZBUFFER);

  myContext->SetDisplayMode(AIS_Shaded, Standard_True);
}

const Handle(AIS_InteractiveContext) & OccView::getContext() const {
  return myContext;
}

void OccView::paintEvent(QPaintEvent * /*theEvent*/) {
  if (myContext.IsNull()) {
    init();
  }

  myView->Redraw();
}

void OccView::resizeEvent(QResizeEvent * /*theEvent*/) {
  if (!myView.IsNull()) {
    myView->MustBeResized();
  }
}

void OccView::fitAll(void) {
  myView->FitAll();
  myView->ZFitAll();
  myView->Redraw();
}

void OccView::select(void) { mouseButtonLeftMode = mouse_button_left_select; }

void OccView::reset(void) { myView->Reset(); }

void OccView::pan(void) {
  myCurrentMode = CurAction3d_DynamicPanning;
  mouseButtonLeftMode = mouse_button_left_pan;
}

void OccView::zoom(void) { myCurrentMode = CurAction3d_DynamicZooming; }

void OccView::rotate(void) {
  myCurrentMode = CurAction3d_DynamicRotation;
  mouseButtonLeftMode = mouse_button_left_rotate;
}

void OccView::mousePressEvent(QMouseEvent *theEvent) {
  if (theEvent->button() == Qt::LeftButton) {
    onLButtonDown((theEvent->buttons() | theEvent->modifiers()),
                  theEvent->pos());
  } else if (theEvent->button() == Qt::MidButton) {
    onMButtonDown((theEvent->buttons() | theEvent->modifiers()),
                  theEvent->pos());
  } else if (theEvent->button() == Qt::RightButton) {
    onRButtonDown((theEvent->buttons() | theEvent->modifiers()),
                  theEvent->pos());
  }
}

void OccView::mouseReleaseEvent(QMouseEvent *theEvent) {
  if (theEvent->button() == Qt::LeftButton) {
    onLButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
  } else if (theEvent->button() == Qt::MidButton) {
    onMButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
  } else if (theEvent->button() == Qt::RightButton) {
    onRButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
  }
}

void OccView::mouseMoveEvent(QMouseEvent *theEvent) {
  onMouseMove(theEvent->buttons(), theEvent->pos());
}

void OccView::wheelEvent(QWheelEvent *theEvent) {
  onMouseWheel(theEvent->buttons(), theEvent->delta(), theEvent->pos());
}

void OccView::onLButtonDown(const int /*theFlags*/, const QPoint thePoint) {
  // Save the current mouse coordinate in min.
  myXmin = thePoint.x();
  myYmin = thePoint.y();
  myXmax = thePoint.x();
  myYmax = thePoint.y();
  if (mouseButtonLeftMode == mouse_button_left_rotate) {
    myView->StartRotation(thePoint.x(), thePoint.y());
  }
}

void OccView::onMButtonDown(const int /*theFlags*/, const QPoint thePoint) {
  // Save the current mouse coordinate in min.
  myXmin = thePoint.x();
  myYmin = thePoint.y();
  myXmax = thePoint.x();
  myYmax = thePoint.y();
  if (myCurrentMode == CurAction3d_DynamicRotation) {
    myView->StartRotation(thePoint.x(), thePoint.y());
  }
}

void OccView::onRButtonDown(const int /*theFlags*/, const QPoint /*thePoint*/) {

}

void OccView::onMouseWheel(const int /*theFlags*/, const int theDelta,
                           const QPoint thePoint) {
  Standard_Integer aFactor = 16;

  Standard_Integer aX = thePoint.x();
  Standard_Integer aY = thePoint.y();

  if (theDelta > 0) {
    aX += aFactor;
    aY += aFactor;
  } else {
    aX -= aFactor;
    aY -= aFactor;
  }

  myView->Zoom(thePoint.x(), thePoint.y(), aX, aY);
}

void OccView::addItemInPopup(QMenu * /*theMenu*/) {}

void OccView::popup(const int /*x*/, const int /*y*/) {}

void OccView::onLButtonUp(const int theFlags, const QPoint thePoint) {
  // Hide the QRubberBand
  if (myRectBand) {
    myRectBand->hide();
  }

  // Ctrl for multi selection.
  if (thePoint.x() == myXmin && thePoint.y() == myYmin) {
    if (theFlags & Qt::ControlModifier) {
      multiInputEvent(thePoint.x(), thePoint.y());
    } else {
      inputEvent(thePoint.x(), thePoint.y());
    }
  }
}

void OccView::onMButtonUp(const int /*theFlags*/, const QPoint thePoint) {
  if (thePoint.x() == myXmin && thePoint.y() == myYmin) {
    panByMiddleButton(thePoint);
  }
}

void OccView::onRButtonUp(const int /*theFlags*/, const QPoint thePoint) {
  popup(thePoint.x(), thePoint.y());
}

void OccView::onMouseMove(const int theFlags, const QPoint thePoint) {
  // Draw the rubber band.
  if (theFlags & Qt::LeftButton) {
    switch (mouseButtonLeftMode) {
    case mouse_button_left_rotate:
      myView->Rotation(thePoint.x(), thePoint.y());
      break;
    case mouse_button_left_pan:
      myView->Pan(thePoint.x() - myXmax, myYmax - thePoint.y());
      myXmax = thePoint.x();
      myYmax = thePoint.y();
      break;

    default:
      break;
    }
    // drawRubberBand(myXmin, myYmin, thePoint.x(), thePoint.y());

    // dragEvent(thePoint.x(), thePoint.y());
  }

  // Ctrl for multi selection.
  if (theFlags & Qt::ControlModifier) {
    multiMoveEvent(thePoint.x(), thePoint.y());
  } else {
    moveEvent(thePoint.x(), thePoint.y());
  }

  // Middle button.
  if (theFlags & Qt::MidButton) {
    switch (myCurrentMode) {
    case CurAction3d_DynamicRotation:
      myView->Rotation(thePoint.x(), thePoint.y());
      break;

    case CurAction3d_DynamicZooming:
      myView->Zoom(myXmin, myYmin, thePoint.x(), thePoint.y());
      break;

    case CurAction3d_DynamicPanning:
      myView->Pan(thePoint.x() - myXmax, myYmax - thePoint.y());
      myXmax = thePoint.x();
      myYmax = thePoint.y();
      break;

    default:
      break;
    }
  }
}

void OccView::dragEvent(const int x, const int y) {
  myContext->Select(myXmin, myYmin, x, y, myView, Standard_True);

  emit selectionChanged();
}

void OccView::multiDragEvent(const int x, const int y) {
  myContext->ShiftSelect(myXmin, myYmin, x, y, myView, Standard_True);

  emit selectionChanged();
}

void OccView::inputEvent(const int x, const int y) {
  Q_UNUSED(x);
  Q_UNUSED(y);

  myContext->Select(Standard_True);

  emit selectionChanged();
}

void OccView::multiInputEvent(const int x, const int y) {
  Q_UNUSED(x);
  Q_UNUSED(y);

  myContext->ShiftSelect(Standard_True);

  emit selectionChanged();
}

void OccView::moveEvent(const int x, const int y) {
  myContext->MoveTo(x, y, myView, Standard_True);
}

void OccView::multiMoveEvent(const int x, const int y) {
  myContext->MoveTo(x, y, myView, Standard_True);
}

void OccView::drawRubberBand(const int minX, const int minY, const int maxX,
                             const int maxY) {
  QRect aRect;

  // Set the rectangle correctly.
  (minX < maxX) ? (aRect.setX(minX)) : (aRect.setX(maxX));
  (minY < maxY) ? (aRect.setY(minY)) : (aRect.setY(maxY));

  aRect.setWidth(abs(maxX - minX));
  aRect.setHeight(abs(maxY - minY));

  if (!myRectBand) {
    myRectBand = new QRubberBand(QRubberBand::Rectangle, this);

    // setStyle is important, set to windows style will just draw
    // rectangle frame, otherwise will draw a solid rectangle.
    myRectBand->setStyle(QStyleFactory::create("windows"));
  }

  myRectBand->setGeometry(aRect);
  myRectBand->show();
}

void OccView::panByMiddleButton(const QPoint &thePoint) {
  Standard_Integer aCenterX = 0;
  Standard_Integer aCenterY = 0;

  QSize aSize = size();

  aCenterX = aSize.width() / 2;
  aCenterY = aSize.height() / 2;

  myView->Pan(aCenterX - thePoint.x(), thePoint.y() - aCenterY);
}

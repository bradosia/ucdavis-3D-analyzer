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

#include "MainWidget.hpp"

static Handle(Graphic3d_GraphicDriver) & GetGraphicDriver() {
  static Handle(Graphic3d_GraphicDriver) aGraphicDriver;
  return aGraphicDriver;
}

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

MapViewerOCC::MapViewerOCC(QWidget *parent)
    : QWidget(parent), myXmin(0), myYmin(0), myXmax(0), myYmax(0),
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

MapViewerOCC::~MapViewerOCC() { myViewer->Remove(); }

void MapViewerOCC::setInitCallback(std::function<void(void)> cb_) {
  initCallback = cb_;
}

void MapViewerOCC::init() {
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

  // view initialized callback
  if (initCallback) {
    initCallback();
  }
}

const Handle(AIS_InteractiveContext) & MapViewerOCC::getContext() const {
  return myContext;
}

void MapViewerOCC::paintEvent(QPaintEvent * /*theEvent*/) {
  if (myContext.IsNull()) {
    init();
  }

  myView->Redraw();
}

void MapViewerOCC::resizeEvent(QResizeEvent * /*theEvent*/) {
  if (!myView.IsNull()) {
    myView->MustBeResized();
  }
}

void MapViewerOCC::fitAll(void) {
  myView->FitAll();
  myView->ZFitAll();
  myView->Redraw();
}

void MapViewerOCC::select(void) {
  mouseButtonLeftMode = mouse_button_left_select;
}

void MapViewerOCC::reset(void) { myView->Reset(); }

void MapViewerOCC::pan(void) {
  myCurrentMode = CurAction3d_DynamicPanning;
  mouseButtonLeftMode = mouse_button_left_pan;
}

void MapViewerOCC::zoom(void) { myCurrentMode = CurAction3d_DynamicZooming; }

void MapViewerOCC::rotate(void) {
  myCurrentMode = CurAction3d_DynamicRotation;
  mouseButtonLeftMode = mouse_button_left_rotate;
}

void MapViewerOCC::mousePressEvent(QMouseEvent *theEvent) {
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

void MapViewerOCC::mouseReleaseEvent(QMouseEvent *theEvent) {
  if (theEvent->button() == Qt::LeftButton) {
    onLButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
  } else if (theEvent->button() == Qt::MidButton) {
    onMButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
  } else if (theEvent->button() == Qt::RightButton) {
    onRButtonUp(theEvent->buttons() | theEvent->modifiers(), theEvent->pos());
  }
}

void MapViewerOCC::mouseMoveEvent(QMouseEvent *theEvent) {
  onMouseMove(theEvent->buttons(), theEvent->pos());
}

void MapViewerOCC::wheelEvent(QWheelEvent *theEvent) {
  onMouseWheel(theEvent->buttons(), theEvent->delta(), theEvent->pos());
}

void MapViewerOCC::onLButtonDown(const int /*theFlags*/,
                                 const QPoint thePoint) {
  // Save the current mouse coordinate in min.
  myXmin = thePoint.x();
  myYmin = thePoint.y();
  myXmax = thePoint.x();
  myYmax = thePoint.y();
  if (mouseButtonLeftMode == mouse_button_left_rotate) {
    myView->StartRotation(thePoint.x(), thePoint.y());
  }
}

void MapViewerOCC::onMButtonDown(const int /*theFlags*/,
                                 const QPoint thePoint) {
  // Save the current mouse coordinate in min.
  myXmin = thePoint.x();
  myYmin = thePoint.y();
  myXmax = thePoint.x();
  myYmax = thePoint.y();
  if (myCurrentMode == CurAction3d_DynamicRotation) {
    myView->StartRotation(thePoint.x(), thePoint.y());
  }
}

void MapViewerOCC::onRButtonDown(const int /*theFlags*/,
                                 const QPoint /*thePoint*/) {}

void MapViewerOCC::onMouseWheel(const int /*theFlags*/, const int theDelta,
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

void MapViewerOCC::addItemInPopup(QMenu * /*theMenu*/) {}

void MapViewerOCC::popup(const int /*x*/, const int /*y*/) {}

void MapViewerOCC::onLButtonUp(const int theFlags, const QPoint thePoint) {
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

void MapViewerOCC::onMButtonUp(const int /*theFlags*/, const QPoint thePoint) {
  if (thePoint.x() == myXmin && thePoint.y() == myYmin) {
    panByMiddleButton(thePoint);
  }
}

void MapViewerOCC::onRButtonUp(const int /*theFlags*/, const QPoint thePoint) {
  popup(thePoint.x(), thePoint.y());
}

void MapViewerOCC::onMouseMove(const int theFlags, const QPoint thePoint) {
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
    drawRubberBand(myXmin, myYmin, thePoint.x(), thePoint.y());

    dragEvent(thePoint.x(), thePoint.y());
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

void MapViewerOCC::dragEvent(const int x, const int y) {
  myContext->Select(myXmin, myYmin, x, y, myView, Standard_True);

  emit selectionChanged();
}

void MapViewerOCC::multiDragEvent(const int x, const int y) {
  myContext->ShiftSelect(myXmin, myYmin, x, y, myView, Standard_True);

  emit selectionChanged();
}

void MapViewerOCC::inputEvent(const int x, const int y) {
  Q_UNUSED(x);
  Q_UNUSED(y);

  myContext->Select(Standard_True);

  emit selectionChanged();
}

void MapViewerOCC::multiInputEvent(const int x, const int y) {
  Q_UNUSED(x);
  Q_UNUSED(y);

  myContext->ShiftSelect(Standard_True);

  emit selectionChanged();
}

void MapViewerOCC::moveEvent(const int x, const int y) {
  myContext->MoveTo(x, y, myView, Standard_True);
}

void MapViewerOCC::multiMoveEvent(const int x, const int y) {
  myContext->MoveTo(x, y, myView, Standard_True);
}

void MapViewerOCC::drawRubberBand(const int minX, const int minY,
                                  const int maxX, const int maxY) {
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

void MapViewerOCC::panByMiddleButton(const QPoint &thePoint) {
  Standard_Integer aCenterX = 0;
  Standard_Integer aCenterY = 0;

  QSize aSize = size();

  aCenterX = aSize.width() / 2;
  aCenterY = aSize.height() / 2;

  myView->Pan(aCenterX - thePoint.x(), thePoint.y() - aCenterY);
}

void MapViewerOCC::addMarker(double height, double radius, double r, double g, double b,
               double x, double y, double z) {
  makeCylinderMarker(myContext, height, radius, r, g, b, x, y, z);
}

void MapViewerOCC::generateMap() {
  // create the shape
  TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(1000, 1000, 5.0).Shape();
  Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
  anAisBox->SetColor(Quantity_NOC_AZURE);

  // MapViewerOCC_Widget->getContext()->Display(anAisBox, Standard_True);
  // textured shape
  Handle(AIS_TexturedShape) aTShape = new AIS_TexturedShape(aTopoBox);
  TCollection_AsciiString aFile(
      "../ucdavis-3D-analyzer/resources/map_model/map/davis.png");
  aTShape->SetTextureFileName(aFile);
  aTShape->SetTextureMapOn();
  // int nRepeat = 1;
  double toScale = 1;
  // aTShape->SetTextureRepeat(Standard_True, nRepeat, nRepeat);
  aTShape->SetTextureRepeat(false, 1, 1);
  aTShape->SetTextureScale(Standard_True, toScale, toScale);
  aTShape->SetTextureOrigin(Standard_True, 0, 0);
  // aTShape->DisableTextureModulate();
  aTShape->SetDisplayMode(3); // mode 3 is "textured" mode
  aTShape->SetMaterial(Graphic3d_NOM_SILVER);
  // MapViewerOCC_Widget->getContext()->SetDisplayMode(aTShape, 3);
  // MapViewerOCC_Widget->getContext()->Display(aTShape, 3,-1);
  myContext->Display(aTShape, Standard_True);
  // MapViewerOCC_Widget->getContext()->Display(aTShape);
  myContext->UpdateCurrentViewer();
  aTShape->UpdateAttributes();
}

} // namespace UCD3DEM

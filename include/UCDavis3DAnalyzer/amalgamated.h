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

#ifndef PKA_AMALGAMATED_H
#define PKA_AMALGAMATED_H

// c++17
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <thread>

// c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>     /* srand, rand */

/*
 * Configuration
 */
#include <UCDavis3DAnalyzer/config.h>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 */
#include "rapidjson/document.h"
#include "rapidjson/reader.h" // rapidjson::ParseResult
#include "rapidjson/stringbuffer.h"

/* OSIsoft API
 */
#include "UCDavis3DAnalyzer/osisoft_pi_api.h"

/* openCascade (OCCT) 7.4.0
 * OCCT library is designed to be truly modular and extensible, providing C++
 * classes for: -Basic data structures (geometric modeling, visualization,
 * interactive selection and application specific services); -Modeling
 * algorithms; -Working with mesh (faceted) data; -Data interoperability with
 * neutral formats (IGES, STEP);
 */
#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <gp_Pln.hxx>

#include <gp_Lin2d.hxx>

#include <Geom_ConicalSurface.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <TColgp_Array1OfPnt2d.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>

#include <BRepLib.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>

#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>

#include <AIS_Shape.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <Interface_Static.hxx>
#include <STEPControl_Writer.hxx>
#include <TopoDS_Edge.hxx>
#include <XCAFDoc_ColorTool.hxx>

#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_Handle.hxx>
// textured shape
#include <AIS_TexturedShape.hxx>

#include <Quantity_Color.hxx>

#ifdef WIN32
#include <WNT_Window.hxx>
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
#include <Cocoa_Window.hxx>
#else
#undef Bool
#undef CursorShape
#undef None
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef Expose
#include <Xw_Window.hxx>
#endif

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QRubberBand>
#include <QString>
#include <QToolBar>
#include <QTreeView>
#include <QMouseEvent>
#include <QStyleFactory>
#include <QTranslator>

/*
 * 3D View
 */
#include "UCDavis3DAnalyzer/occView.h"
#include "UCDavis3DAnalyzer/view3DMap.h"

/*
 * UCD3DA = UC Davis 3D Analyzer
 */
namespace UCD3DA {

/*
 * Holds a openCascade (OCCT) shape and performs data exchange
 * Internal data is public since this is suppose to be
 * a convenience abstraction.
 */
class OCCT_Shape {
public:
  std::unique_ptr<TopoDS_Shape> shape_;
  int writeSTEP(char *path);
};

} // namespace UCD3DA

#endif

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
#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_map>

// c
#include <stdio.h>
#include <string.h>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 */
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h" // rapidjson::ParseResult

/* OSIsoft API
 */
#include "UCDavis3DAnalyzer/osisoft_pi_api.h"

/* openCascade (OCCT) 7.4.0
 * OCCT library is designed to be truly modular and extensible, providing C++ classes for:
 * -Basic data structures (geometric modeling, visualization, interactive selection and
 * application specific services);
 * -Modeling algorithms;
 * -Working with mesh (faceted) data;
 * -Data interoperability with neutral formats (IGES, STEP);
 */
#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <gp_Pln.hxx>

#include <gp_Lin2d.hxx>

#include <Geom_ConicalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_CylindricalSurface.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

#include <BRepLib.hxx>

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>

#include <AIS_Shape.hxx>

#include <STEPControl_Writer.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <Interface_Static.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <XCAFDoc_ColorTool.hxx>

#include <AIS_InteractiveContext.hxx>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QApplication>
#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTreeView>
#include <QOpenGLWidget>
#include <QMessageBox>
#include <QToolBar>
#include <QMenu>
#include <QRubberBand>
#include <QOpenGLContext>

/* High level code for project
 */
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

} // namespace PKA

#endif

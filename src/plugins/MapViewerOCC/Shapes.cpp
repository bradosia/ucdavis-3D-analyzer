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
#include "Shapes.hpp"

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

void makeBox(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(3.0, 4.0, 5.0).Shape();
  Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);

  anAisBox->SetColor(Quantity_NOC_AZURE);

  interactiveContextHandle->Display(anAisBox, Standard_True);
}

void makeCone(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(0.0, 10.0, 0.0));

  TopoDS_Shape aTopoReducer =
      BRepPrimAPI_MakeCone(anAxis, 3.0, 1.5, 5.0).Shape();
  Handle(AIS_Shape) anAisReducer = new AIS_Shape(aTopoReducer);

  anAisReducer->SetColor(Quantity_NOC_BISQUE);

  anAxis.SetLocation(gp_Pnt(8.0, 10.0, 0.0));
  TopoDS_Shape aTopoCone = BRepPrimAPI_MakeCone(anAxis, 3.0, 0.0, 5.0).Shape();
  Handle(AIS_Shape) anAisCone = new AIS_Shape(aTopoCone);

  anAisCone->SetColor(Quantity_NOC_CHOCOLATE);

  interactiveContextHandle->Display(anAisReducer, Standard_True);
  interactiveContextHandle->Display(anAisCone, Standard_True);
}

void makeSphere(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(0.0, 20.0, 0.0));

  TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 3.0).Shape();
  Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);

  anAisSphere->SetColor(Quantity_NOC_BLUE1);

  interactiveContextHandle->Display(anAisSphere, Standard_True);
}

void makeCylinder(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(0.0, 30.0, 0.0));

  TopoDS_Shape aTopoCylinder =
      BRepPrimAPI_MakeCylinder(anAxis, 3.0, 5.0).Shape();
  Handle(AIS_Shape) anAisCylinder = new AIS_Shape(aTopoCylinder);

  anAisCylinder->SetColor(Quantity_NOC_RED);

  anAxis.SetLocation(gp_Pnt(8.0, 30.0, 0.0));
  TopoDS_Shape aTopoPie =
      BRepPrimAPI_MakeCylinder(anAxis, 3.0, 5.0, M_PI_2 * 3.0).Shape();
  Handle(AIS_Shape) anAisPie = new AIS_Shape(aTopoPie);

  anAisPie->SetColor(Quantity_NOC_TAN);

  interactiveContextHandle->Display(anAisCylinder, Standard_True);
  interactiveContextHandle->Display(anAisPie, Standard_True);
}

void makeTorus(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(0.0, 40.0, 0.0));

  TopoDS_Shape aTopoTorus = BRepPrimAPI_MakeTorus(anAxis, 3.0, 1.0).Shape();
  Handle(AIS_Shape) anAisTorus = new AIS_Shape(aTopoTorus);

  anAisTorus->SetColor(Quantity_NOC_YELLOW);

  anAxis.SetLocation(gp_Pnt(8.0, 40.0, 0.0));
  TopoDS_Shape aTopoElbow =
      BRepPrimAPI_MakeTorus(anAxis, 3.0, 1.0, M_PI_2).Shape();
  Handle(AIS_Shape) anAisElbow = new AIS_Shape(aTopoElbow);

  anAisElbow->SetColor(Quantity_NOC_THISTLE);

  interactiveContextHandle->Display(anAisTorus, Standard_True);
  interactiveContextHandle->Display(anAisElbow, Standard_True);
}

void makeFillet(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(0.0, 50.0, 0.0));

  TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
  BRepFilletAPI_MakeFillet MF(aTopoBox);

  // Add all the edges to fillet.
  for (TopExp_Explorer ex(aTopoBox, TopAbs_EDGE); ex.More(); ex.Next()) {
    MF.Add(1.0, TopoDS::Edge(ex.Current()));
  }

  Handle(AIS_Shape) anAisShape = new AIS_Shape(MF.Shape());
  anAisShape->SetColor(Quantity_NOC_VIOLET);

  interactiveContextHandle->Display(anAisShape, Standard_True);
}

void makeChamfer(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(8.0, 50.0, 0.0));

  TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
  BRepFilletAPI_MakeChamfer MC(aTopoBox);
  TopTools_IndexedDataMapOfShapeListOfShape aEdgeFaceMap;

  TopExp::MapShapesAndAncestors(aTopoBox, TopAbs_EDGE, TopAbs_FACE,
                                aEdgeFaceMap);

  for (Standard_Integer i = 1; i <= aEdgeFaceMap.Extent(); ++i) {
    TopoDS_Edge anEdge = TopoDS::Edge(aEdgeFaceMap.FindKey(i));
    TopoDS_Face aFace = TopoDS::Face(aEdgeFaceMap.FindFromIndex(i).First());

    MC.Add(0.6, 0.6, anEdge, aFace);
  }

  Handle(AIS_Shape) anAisShape = new AIS_Shape(MC.Shape());
  anAisShape->SetColor(Quantity_NOC_TOMATO);

  interactiveContextHandle->Display(anAisShape, Standard_True);
}

void makeExtrude(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  // prism a vertex result is an edge.
  TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(gp_Pnt(0.0, 60.0, 0.0));
  TopoDS_Shape aPrismVertex =
      BRepPrimAPI_MakePrism(aVertex, gp_Vec(0.0, 0.0, 5.0));
  Handle(AIS_Shape) anAisPrismVertex = new AIS_Shape(aPrismVertex);

  // prism an edge result is a face.
  TopoDS_Edge anEdge =
      BRepBuilderAPI_MakeEdge(gp_Pnt(5.0, 60.0, 0.0), gp_Pnt(10.0, 60.0, 0.0));
  TopoDS_Shape aPrismEdge =
      BRepPrimAPI_MakePrism(anEdge, gp_Vec(0.0, 0.0, 5.0));
  Handle(AIS_Shape) anAisPrismEdge = new AIS_Shape(aPrismEdge);

  // prism a wire result is a shell.
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(16.0, 60.0, 0.0));

  TopoDS_Edge aCircleEdge = BRepBuilderAPI_MakeEdge(gp_Circ(anAxis, 3.0));
  TopoDS_Wire aCircleWire = BRepBuilderAPI_MakeWire(aCircleEdge);
  TopoDS_Shape aPrismCircle =
      BRepPrimAPI_MakePrism(aCircleWire, gp_Vec(0.0, 0.0, 5.0));
  Handle(AIS_Shape) anAisPrismCircle = new AIS_Shape(aPrismCircle);

  // prism a face or a shell result is a solid.
  anAxis.SetLocation(gp_Pnt(24.0, 60.0, 0.0));
  TopoDS_Edge aEllipseEdge =
      BRepBuilderAPI_MakeEdge(gp_Elips(anAxis, 3.0, 2.0));
  TopoDS_Wire aEllipseWire = BRepBuilderAPI_MakeWire(aEllipseEdge);
  TopoDS_Face aEllipseFace =
      BRepBuilderAPI_MakeFace(gp_Pln(gp::XOY()), aEllipseWire);
  TopoDS_Shape aPrismEllipse =
      BRepPrimAPI_MakePrism(aEllipseFace, gp_Vec(0.0, 0.0, 5.0));
  Handle(AIS_Shape) anAisPrismEllipse = new AIS_Shape(aPrismEllipse);

  anAisPrismVertex->SetColor(Quantity_NOC_PAPAYAWHIP);
  anAisPrismEdge->SetColor(Quantity_NOC_PEACHPUFF);
  anAisPrismCircle->SetColor(Quantity_NOC_PERU);
  anAisPrismEllipse->SetColor(Quantity_NOC_PINK);

  interactiveContextHandle->Display(anAisPrismVertex, Standard_True);
  interactiveContextHandle->Display(anAisPrismEdge, Standard_True);
  interactiveContextHandle->Display(anAisPrismCircle, Standard_True);
  interactiveContextHandle->Display(anAisPrismEllipse, Standard_True);
}

void makeRevolve(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax1 anAxis;

  // revol a vertex result is an edge.
  anAxis.SetLocation(gp_Pnt(0.0, 70.0, 0.0));
  TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(gp_Pnt(2.0, 70.0, 0.0));
  TopoDS_Shape aRevolVertex = BRepPrimAPI_MakeRevol(aVertex, anAxis);
  Handle(AIS_Shape) anAisRevolVertex = new AIS_Shape(aRevolVertex);

  // revol an edge result is a face.
  anAxis.SetLocation(gp_Pnt(8.0, 70.0, 0.0));
  TopoDS_Edge anEdge =
      BRepBuilderAPI_MakeEdge(gp_Pnt(6.0, 70.0, 0.0), gp_Pnt(6.0, 70.0, 5.0));
  TopoDS_Shape aRevolEdge = BRepPrimAPI_MakeRevol(anEdge, anAxis);
  Handle(AIS_Shape) anAisRevolEdge = new AIS_Shape(aRevolEdge);

  // revol a wire result is a shell.
  anAxis.SetLocation(gp_Pnt(20.0, 70.0, 0.0));
  anAxis.SetDirection(gp::DY());

  TopoDS_Edge aCircleEdge = BRepBuilderAPI_MakeEdge(
      gp_Circ(gp_Ax2(gp_Pnt(15.0, 70.0, 0.0), gp::DZ()), 1.5));
  TopoDS_Wire aCircleWire = BRepBuilderAPI_MakeWire(aCircleEdge);
  TopoDS_Shape aRevolCircle =
      BRepPrimAPI_MakeRevol(aCircleWire, anAxis, M_PI_2);
  Handle(AIS_Shape) anAisRevolCircle = new AIS_Shape(aRevolCircle);

  // revol a face result is a solid.
  anAxis.SetLocation(gp_Pnt(30.0, 70.0, 0.0));
  anAxis.SetDirection(gp::DY());

  TopoDS_Edge aEllipseEdge = BRepBuilderAPI_MakeEdge(
      gp_Elips(gp_Ax2(gp_Pnt(25.0, 70.0, 0.0), gp::DZ()), 3.0, 2.0));
  TopoDS_Wire aEllipseWire = BRepBuilderAPI_MakeWire(aEllipseEdge);
  TopoDS_Face aEllipseFace =
      BRepBuilderAPI_MakeFace(gp_Pln(gp::XOY()), aEllipseWire);
  TopoDS_Shape aRevolEllipse =
      BRepPrimAPI_MakeRevol(aEllipseFace, anAxis, M_PI_4);
  Handle(AIS_Shape) anAisRevolEllipse = new AIS_Shape(aRevolEllipse);

  anAisRevolVertex->SetColor(Quantity_NOC_LIMEGREEN);
  anAisRevolEdge->SetColor(Quantity_NOC_LINEN);
  anAisRevolCircle->SetColor(Quantity_NOC_MAGENTA1);
  anAisRevolEllipse->SetColor(Quantity_NOC_MAROON);

  interactiveContextHandle->Display(anAisRevolVertex, Standard_True);
  interactiveContextHandle->Display(anAisRevolEdge, Standard_True);
  interactiveContextHandle->Display(anAisRevolCircle, Standard_True);
  interactiveContextHandle->Display(anAisRevolEllipse, Standard_True);
}

void makeLoft(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  // bottom wire.
  TopoDS_Edge aCircleEdge = BRepBuilderAPI_MakeEdge(
      gp_Circ(gp_Ax2(gp_Pnt(0.0, 80.0, 0.0), gp::DZ()), 1.5));
  TopoDS_Wire aCircleWire = BRepBuilderAPI_MakeWire(aCircleEdge);

  // top wire.
  BRepBuilderAPI_MakePolygon aPolygon;
  aPolygon.Add(gp_Pnt(-3.0, 77.0, 6.0));
  aPolygon.Add(gp_Pnt(3.0, 77.0, 6.0));
  aPolygon.Add(gp_Pnt(3.0, 83.0, 6.0));
  aPolygon.Add(gp_Pnt(-3.0, 83.0, 6.0));
  aPolygon.Close();

  BRepOffsetAPI_ThruSections aShellGenerator;
  BRepOffsetAPI_ThruSections aSolidGenerator(true);

  aShellGenerator.AddWire(aCircleWire);
  aShellGenerator.AddWire(aPolygon.Wire());

  aSolidGenerator.AddWire(aCircleWire);
  aSolidGenerator.AddWire(aPolygon.Wire());

  // translate the solid.
  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(18.0, 0.0, 0.0));
  BRepBuilderAPI_Transform aTransform(aSolidGenerator.Shape(), aTrsf);

  Handle(AIS_Shape) anAisShell = new AIS_Shape(aShellGenerator.Shape());
  Handle(AIS_Shape) anAisSolid = new AIS_Shape(aTransform.Shape());

  anAisShell->SetColor(Quantity_NOC_OLIVEDRAB);
  anAisSolid->SetColor(Quantity_NOC_PEACHPUFF);

  interactiveContextHandle->Display(anAisShell, Standard_True);
  interactiveContextHandle->Display(anAisSolid, Standard_True);
}

void makeCut(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(0.0, 90.0, 0.0));

  TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
  TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 2.5).Shape();
  TopoDS_Shape aCuttedShape1 = BRepAlgoAPI_Cut(aTopoBox, aTopoSphere);
  TopoDS_Shape aCuttedShape2 = BRepAlgoAPI_Cut(aTopoSphere, aTopoBox);

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(8.0, 0.0, 0.0));
  BRepBuilderAPI_Transform aTransform1(aCuttedShape1, aTrsf);

  aTrsf.SetTranslation(gp_Vec(16.0, 0.0, 0.0));
  BRepBuilderAPI_Transform aTransform2(aCuttedShape2, aTrsf);

  Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
  Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);
  Handle(AIS_Shape) anAisCuttedShape1 = new AIS_Shape(aTransform1.Shape());
  Handle(AIS_Shape) anAisCuttedShape2 = new AIS_Shape(aTransform2.Shape());

  anAisBox->SetColor(Quantity_NOC_SPRINGGREEN);
  anAisSphere->SetColor(Quantity_NOC_STEELBLUE);
  anAisCuttedShape1->SetColor(Quantity_NOC_TAN);
  anAisCuttedShape2->SetColor(Quantity_NOC_SALMON);

  interactiveContextHandle->Display(anAisBox, Standard_True);
  interactiveContextHandle->Display(anAisSphere, Standard_True);
  interactiveContextHandle->Display(anAisCuttedShape1, Standard_True);
  interactiveContextHandle->Display(anAisCuttedShape2, Standard_True);
}

void makeFuse(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(0.0, 100.0, 0.0));

  TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
  TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 2.5).Shape();
  TopoDS_Shape aFusedShape = BRepAlgoAPI_Fuse(aTopoBox, aTopoSphere);

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(8.0, 0.0, 0.0));
  BRepBuilderAPI_Transform aTransform(aFusedShape, aTrsf);

  Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
  Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);
  Handle(AIS_Shape) anAisFusedShape = new AIS_Shape(aTransform.Shape());

  anAisBox->SetColor(Quantity_NOC_SPRINGGREEN);
  anAisSphere->SetColor(Quantity_NOC_STEELBLUE);
  anAisFusedShape->SetColor(Quantity_NOC_ROSYBROWN);

  interactiveContextHandle->Display(anAisBox, Standard_True);
  interactiveContextHandle->Display(anAisSphere, Standard_True);
  interactiveContextHandle->Display(anAisFusedShape, Standard_True);
}

void makeCommon(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(0.0, 110.0, 0.0));

  TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
  TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 2.5).Shape();
  TopoDS_Shape aCommonShape = BRepAlgoAPI_Common(aTopoBox, aTopoSphere);

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(8.0, 0.0, 0.0));
  BRepBuilderAPI_Transform aTransform(aCommonShape, aTrsf);

  Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
  Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);
  Handle(AIS_Shape) anAisCommonShape = new AIS_Shape(aTransform.Shape());

  anAisBox->SetColor(Quantity_NOC_SPRINGGREEN);
  anAisSphere->SetColor(Quantity_NOC_STEELBLUE);
  anAisCommonShape->SetColor(Quantity_NOC_ROYALBLUE);

  interactiveContextHandle->Display(anAisBox, Standard_True);
  interactiveContextHandle->Display(anAisSphere, Standard_True);
  interactiveContextHandle->Display(anAisCommonShape, Standard_True);
}

void makeCylindricalHelix(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  Standard_Real aRadius = 3.0;
  Standard_Real aPitch = 1.0;

  // the pcurve is a 2d line in the parametric space.
  gp_Lin2d aLine2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(aRadius, aPitch));

  Handle(Geom2d_TrimmedCurve) aSegment =
      GCE2d_MakeSegment(aLine2d, 0.0, M_PI * 2.0).Value();

  Handle(Geom_CylindricalSurface) aCylinder =
      new Geom_CylindricalSurface(gp::XOY(), aRadius);

  TopoDS_Edge aHelixEdge =
      BRepBuilderAPI_MakeEdge(aSegment, aCylinder, 0.0, 6.0 * M_PI).Edge();

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(0.0, 120.0, 0.0));
  BRepBuilderAPI_Transform aTransform(aHelixEdge, aTrsf);

  Handle(AIS_Shape) anAisHelixCurve = new AIS_Shape(aTransform.Shape());

  interactiveContextHandle->Display(anAisHelixCurve, Standard_True);

  // sweep a circle profile along the helix curve.
  // there is no curve3d in the pcurve edge, so approx one.
  BRepLib::BuildCurve3d(aHelixEdge);

  gp_Ax2 anAxis;
  anAxis.SetDirection(gp_Dir(0.0, 4.0, 1.0));
  anAxis.SetLocation(gp_Pnt(aRadius, 0.0, 0.0));

  gp_Circ aProfileCircle(anAxis, 0.3);

  TopoDS_Edge aProfileEdge = BRepBuilderAPI_MakeEdge(aProfileCircle).Edge();
  TopoDS_Wire aProfileWire = BRepBuilderAPI_MakeWire(aProfileEdge).Wire();
  TopoDS_Face aProfileFace = BRepBuilderAPI_MakeFace(aProfileWire).Face();

  TopoDS_Wire aHelixWire = BRepBuilderAPI_MakeWire(aHelixEdge).Wire();

  BRepOffsetAPI_MakePipe aPipeMaker(aHelixWire, aProfileFace);

  if (aPipeMaker.IsDone()) {
    aTrsf.SetTranslation(gp_Vec(8.0, 120.0, 0.0));
    BRepBuilderAPI_Transform aPipeTransform(aPipeMaker.Shape(), aTrsf);

    Handle(AIS_Shape) anAisPipe = new AIS_Shape(aPipeTransform.Shape());
    anAisPipe->SetColor(Quantity_NOC_CORAL);
    interactiveContextHandle->Display(anAisPipe, Standard_True);
  }
}

/**
 * make conical helix, it is the same as the cylindrical helix,
 * the only different is the surface.
 */
void makeConicalHelix(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  Standard_Real aRadius = 3.0;
  Standard_Real aPitch = 1.0;

  // the pcurve is a 2d line in the parametric space.
  gp_Lin2d aLine2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(aRadius, aPitch));

  Handle(Geom2d_TrimmedCurve) aSegment =
      GCE2d_MakeSegment(aLine2d, 0.0, M_PI * 2.0).Value();

  Handle(Geom_ConicalSurface) aCylinder =
      new Geom_ConicalSurface(gp::XOY(), M_PI / 6.0, aRadius);

  TopoDS_Edge aHelixEdge =
      BRepBuilderAPI_MakeEdge(aSegment, aCylinder, 0.0, 6.0 * M_PI).Edge();

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(18.0, 120.0, 0.0));
  BRepBuilderAPI_Transform aTransform(aHelixEdge, aTrsf);

  Handle(AIS_Shape) anAisHelixCurve = new AIS_Shape(aTransform.Shape());

  interactiveContextHandle->Display(anAisHelixCurve, Standard_True);

  // sweep a circle profile along the helix curve.
  // there is no curve3d in the pcurve edge, so approx one.
  BRepLib::BuildCurve3d(aHelixEdge);

  gp_Ax2 anAxis;
  anAxis.SetDirection(gp_Dir(0.0, 4.0, 1.0));
  anAxis.SetLocation(gp_Pnt(aRadius, 0.0, 0.0));

  gp_Circ aProfileCircle(anAxis, 0.3);

  TopoDS_Edge aProfileEdge = BRepBuilderAPI_MakeEdge(aProfileCircle).Edge();
  TopoDS_Wire aProfileWire = BRepBuilderAPI_MakeWire(aProfileEdge).Wire();
  TopoDS_Face aProfileFace = BRepBuilderAPI_MakeFace(aProfileWire).Face();

  TopoDS_Wire aHelixWire = BRepBuilderAPI_MakeWire(aHelixEdge).Wire();

  BRepOffsetAPI_MakePipe aPipeMaker(aHelixWire, aProfileFace);

  if (aPipeMaker.IsDone()) {
    aTrsf.SetTranslation(gp_Vec(28.0, 120.0, 0.0));
    BRepBuilderAPI_Transform aPipeTransform(aPipeMaker.Shape(), aTrsf);

    Handle(AIS_Shape) anAisPipe = new AIS_Shape(aPipeTransform.Shape());
    anAisPipe->SetColor(Quantity_NOC_DARKGOLDENROD);
    interactiveContextHandle->Display(anAisPipe, Standard_True);
  }
}

void makeToroidalHelix(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle) {
  Standard_Real aRadius = 1.0;
  Standard_Real aSlope = 0.05;

  // the pcurve is a 2d line in the parametric space.
  gp_Lin2d aLine2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(aSlope, 1.0));

  Handle(Geom2d_TrimmedCurve) aSegment =
      GCE2d_MakeSegment(aLine2d, 0.0, M_PI * 2.0).Value();

  Handle(Geom_ToroidalSurface) aCylinder =
      new Geom_ToroidalSurface(gp::XOY(), aRadius * 5.0, aRadius);

  TopoDS_Edge aHelixEdge =
      BRepBuilderAPI_MakeEdge(aSegment, aCylinder, 0.0, 2.0 * M_PI / aSlope)
          .Edge();

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(45.0, 120.0, 0.0));
  BRepBuilderAPI_Transform aTransform(aHelixEdge, aTrsf);

  Handle(AIS_Shape) anAisHelixCurve = new AIS_Shape(aTransform.Shape());

  interactiveContextHandle->Display(anAisHelixCurve, Standard_True);

  // sweep a circle profile along the helix curve.
  // there is no curve3d in the pcurve edge, so approx one.
  BRepLib::BuildCurve3d(aHelixEdge);

  gp_Ax2 anAxis;
  anAxis.SetDirection(gp_Dir(0.0, 0.0, 1.0));
  anAxis.SetLocation(gp_Pnt(aRadius * 6.0, 0.0, 0.0));

  gp_Circ aProfileCircle(anAxis, 0.3);

  TopoDS_Edge aProfileEdge = BRepBuilderAPI_MakeEdge(aProfileCircle).Edge();
  TopoDS_Wire aProfileWire = BRepBuilderAPI_MakeWire(aProfileEdge).Wire();
  TopoDS_Face aProfileFace = BRepBuilderAPI_MakeFace(aProfileWire).Face();

  TopoDS_Wire aHelixWire = BRepBuilderAPI_MakeWire(aHelixEdge).Wire();

  BRepOffsetAPI_MakePipe aPipeMaker(aHelixWire, aProfileFace);

  if (aPipeMaker.IsDone()) {
    aTrsf.SetTranslation(gp_Vec(60.0, 120.0, 0.0));
    BRepBuilderAPI_Transform aPipeTransform(aPipeMaker.Shape(), aTrsf);

    Handle(AIS_Shape) anAisPipe = new AIS_Shape(aPipeTransform.Shape());
    anAisPipe->SetColor(Quantity_NOC_CORNSILK1);
    interactiveContextHandle->Display(anAisPipe, Standard_True);
  }
}

void makeCylinderMarker(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle,
    double height, double radius, double r, double g, double b, double x,
    double y, double z) {
  gp_Ax2 anAxis;
  anAxis.SetLocation(gp_Pnt(x, y, z));
  TopoDS_Shape aTopoReducer =
      BRepPrimAPI_MakeCylinder(anAxis, radius, height).Shape();
  opencascade::handle<AIS_Shape> anAisReducer = new AIS_Shape(aTopoReducer);
  // colors are RGB doubles from 0.0 to 1.0
  anAisReducer->SetColor(
      Quantity_Color(r, g, b, Quantity_TypeOfColor::Quantity_TOC_RGB));
  interactiveContextHandle->Display(anAisReducer, Standard_True);
}

} // namespace UCD3DEM

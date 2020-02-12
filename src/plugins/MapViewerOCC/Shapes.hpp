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

#ifndef MAP_VIEWER_OCC_SHAPES_H
#define MAP_VIEWER_OCC_SHAPES_H

// Universal Include
#include "universalInclude.hpp"

/*
 * UCD3DEM = UC Davis 3D Electricity Map
 */
namespace UCD3DEM {

void makeSphere(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeBox(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeCone(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeCylinder(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeRevolve(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeLoft(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeCut(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeFuse(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeCommon(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeTorus(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeFillet(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeChamfer(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeExtrude(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeCylindricalHelix(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeConicalHelix(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeToroidalHelix(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle);
void makeCylinderMarker(
    opencascade::handle<AIS_InteractiveContext> interactiveContextHandle,
    double height, double radius, double r, double g, double b, double x,
    double y, double z);

} // namespace UCD3DEM

#endif // MAP_VIEWER_OCC_SHAPES_H

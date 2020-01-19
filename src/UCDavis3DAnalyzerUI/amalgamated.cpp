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

#include "UCDavis3DAnalyzer/amalgamated.h"

/*
 * UCD3DA = UC Davis 3D Analyzer
 */
namespace UCD3DA {

int OCCT_Shape::writeSTEP(char *path) {
  STEPControl_Writer writer;
  if (!Interface_Static::SetIVal("write.precision.mode", 1)) {
    // error
  }
  if (!Interface_Static::SetIVal("write.step.assembly", 0)) {
    // error
  }
  if (!Interface_Static::SetCVal("write.step.schema", "DIS")) {
    // error
  }

  // Write file
  STEPControl_StepModelType mode = STEPControl_AsIs;
  // XCAFDoc_ColorTool colorTool;
  // opencascade::handle<XSControl_WorkSession> WS;
  // writer.SetWS(WS,false);
  IFSelect_ReturnStatus stat1 = writer.Transfer(*shape_, mode);
  IFSelect_ReturnStatus stat2 = writer.Write(path);
  return 0;
}

} // namespace UCD3DA

/************************************************************************** *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SO_TABBOXDRAGGER_IV_H
#define SO_TABBOXDRAGGER_IV_H

static const char TABBOXDRAGGER_draggergeometry[] =
  "#Inventor V2.1 ascii\n"
  "\n"
  "\n"
  "DEF TABBOX_INACTIVE_MATERIAL Material { diffuseColor 0.5 0.5 0.5  emissiveColor 0.5 0.5 0.5 }\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "DEF tabBoxScaleTabMaterial Material { diffuseColor 0 0.5 0  emissiveColor 0 0.5 0 }\n"
  "DEF tabBoxScaleTabHints ShapeHints {\n"
  "\n"
  "   vertexOrdering COUNTERCLOCKWISE\n"
  "   shapeType SOLID\n"
  "}\n"
  "\n"
  "\n"
  "DEF tabBoxBoxGeom Separator {\n"
  "   USE TABBOX_INACTIVE_MATERIAL\n"
  "   DrawStyle { style LINES }\n"
  "   PickStyle { style UNPICKABLE }\n"
  "   Cube { }\n"
  "}\n"
  "\n"
  "\n"
  "DEF tabBoxTranslator Separator {\n"
  "   DrawStyle { style INVISIBLE }\n"
  "   Coordinate3 { point [ -1 -1 0, 1 -1 0, 1 1 0, -1 1 0 ] }\n"
  "   IndexedFaceSet { coordIndex [ 0, 1, 2, 3, -1 ] }\n"
  "}\n";

#endif /* ! SO_TABBOXDRAGGER_IV_H */
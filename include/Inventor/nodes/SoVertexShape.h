/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use Coin with software that is incompatible
 *  licensewise with the GPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef COIN_SOVERTEXSHAPE_H
#define COIN_SOVERTEXSHAPE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFNode.h>
#ifndef COIN_INTERNAL
 // For Open Inventor compatibility.
 #include <Inventor/nodes/SoVertexProperty.h>
#endif // !COIN_INTERNAL


class SoNormalCache;
class SoNormalBundle;
class SbVec3f;
class SoTextureCoordinateElement;
class SoCoordinateElement;


class COIN_DLL_API SoVertexShape : public SoShape {
  typedef SoShape inherited;

  SO_NODE_ABSTRACT_HEADER(SoVertexShape);

public:
  static void initClass(void);

  SoSFNode vertexProperty;

  virtual void notify(SoNotList * nl);
  virtual SbBool generateDefaultNormals(SoState * state,
                                        SoNormalBundle * bundle);
  virtual SbBool generateDefaultNormals(SoState * state,
                                        SoNormalCache * cache);
  virtual void write(SoWriteAction * action);

protected:
  SoVertexShape(void);
  virtual ~SoVertexShape();

  virtual SbBool shouldGLRender(SoGLRenderAction * action);

  void setNormalCache(SoState * const state,
                      const int num, const SbVec3f * normals);
  SoNormalCache * getNormalCache(void) const;

  void generateNormals(SoState * const state);
  void getVertexData(SoState * state,
                     const SoCoordinateElement *& coords,
                     const SbVec3f *& normals,
                     const SbBool neednormals);

private:
  SoNormalCache * normalcache;
};

#endif // !COIN_SOVERTEXSHAPE_H

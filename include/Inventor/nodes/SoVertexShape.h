/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
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


class COIN_DLL_EXPORT SoVertexShape : public SoShape {
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
  void generateNormals(SoState * const state);

  virtual void write(SoWriteAction * action);

protected:
  SoVertexShape(void);
  virtual ~SoVertexShape();

  virtual SbBool willUpdateNormalizeElement(SoState *) const;
  virtual SbBool shouldGLRender(SoGLRenderAction * action);

  void setNormalCache(SoState * const state,
                      const int num, const SbVec3f * normals);
  SoNormalCache * getNormalCache(void) const;

  void getVertexData(SoState * state,
                     const SoCoordinateElement *& coords,
                     const SbVec3f *& normals,
                     const SbBool neednormals);

private:
  SoNormalCache * normalcache;
};

#endif // !COIN_SOVERTEXSHAPE_H

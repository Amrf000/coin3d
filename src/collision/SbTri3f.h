#ifndef COIN_SBTRI3F_H
#define COIN_SBTRI3F_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
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
 *  See <URL:http://www.coin3d.org> for  more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <Inventor/SbVec3f.h>

class SbTri3fP;

class SbTri3f {
public:
  SbTri3f(void);
  SbTri3f(const SbTri3f & t);
  SbTri3f(const SbVec3f & a, const SbVec3f & b, const SbVec3f & c);
  ~SbTri3f(void);

  SbTri3f & setValue(const SbTri3f & t);
  SbTri3f & setValue(const SbVec3f & a, const SbVec3f & b, const SbVec3f & c);
  void getValue(SbTri3f & t) const;
  void getValue(SbVec3f & a, SbVec3f & b, SbVec3f & c) const;
  SbVec3f getNormal() const;
  float getDistance(const SbTri3f & t) const;
  static float getDistance(const SbVec3f & p, 
                           const SbVec3f & p1, const SbVec3f & p2);
  float getDistance(const SbVec3f & p) const;
  float getDistance(const SbVec3f & p1, const SbVec3f & p2) const;
  static float sqrDistance(const SbVec3f & a1, const SbVec3f & a2,
                           const SbVec3f & b1, const SbVec3f & b2,
                           float * linP0, float * linP1);
  float sqrDistance(const SbVec3f & p1, 
                    float * pfSParam = NULL, float * pfTParam = NULL) const;

  SbTri3f & operator = (const SbTri3f & t);

  SbBool intersect(const SbTri3f & triangle) const;
  SbBool intersect(const SbTri3f & triangle, float epsilon) const;

  const SbBox3f getBoundingBox(void) const;

private:
  // FIXME: get rid of this -- a triangle is too simple a class to
  // have a private implementation. 20030328 mortene.
  SbTri3fP * const pimpl;
};

#endif // !COIN_SBTRI3F_H

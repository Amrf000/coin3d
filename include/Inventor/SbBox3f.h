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

#ifndef COIN_SBBOX3F_H
#define COIN_SBBOX3F_H

#include <float.h>
#include <stdio.h>

#include <Inventor/SbVec3f.h>

class SbMatrix;

class COIN_DLL_EXPORT SbBox3f {
public:
  SbBox3f(void);
  SbBox3f(const float minx, const float miny, const float minz,
          const float maxx, const float maxy, const float maxz);
  SbBox3f(const SbVec3f & min, const SbVec3f & max);
  ~SbBox3f();

  const SbVec3f & getMin(void) const;
  const SbVec3f & getMax(void) const;

  SbVec3f getCenter(void) const;

  void extendBy(const SbVec3f & point);
  void extendBy(const SbBox3f & box);

  SbBool intersect(const SbVec3f & point) const;
  SbBool intersect(const SbBox3f & box) const;

  void setBounds(const float minx, const float miny, const float minz,
                 const float maxx, const float maxy, const float maxz);
  void setBounds(const SbVec3f & min, const SbVec3f & max);
  void getBounds(float & minx, float & miny, float & minz,
                 float & maxx, float & maxy, float & maxz) const;
  void getBounds(SbVec3f & min, SbVec3f & max) const;

  void getOrigin(float & x0, float & y0, float & z0) const;
  void getSize(float & dx, float & dy, float & dz) const;

  void makeEmpty(void);
  SbBool isEmpty(void) const;
  SbBool hasVolume(void) const;

  void getSpan(const SbVec3f & dir, float & dmin, float & dmax) const;
  void transform(const SbMatrix & matrix);
  float getVolume(void) const;

  SbBool outside(const SbMatrix & mvp, int & cullbits) const;
  SbVec3f getClosestPoint(const SbVec3f & point) const;

  friend COIN_DLL_EXPORT int operator ==(const SbBox3f & b1, const SbBox3f & b2);
  friend COIN_DLL_EXPORT int operator !=(const SbBox3f & b1, const SbBox3f & b2);

  void print(FILE * file) const;

private:
  SbVec3f min, max;
};

COIN_DLL_EXPORT int operator ==(const SbBox3f & b1, const SbBox3f & b2);
COIN_DLL_EXPORT int operator !=(const SbBox3f & b1, const SbBox3f & b2);

#endif // !COIN_SBBOX3F_H

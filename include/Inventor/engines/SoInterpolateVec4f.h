/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

#ifndef __SOINTERPOLATEVEC4F_H__
#define __SOINTERPOLATEVEC4F_H__

#include <Inventor/confdep.h>
#if defined(COIN_EXCLUDE_SOINTERPOLATEVEC4F)
#error "Configuration settings disrespected -- do not include this file!"
#endif // COIN_EXCLUDE_SOINTERPOLATEVEC4F

//$ BEGIN TEMPLATE InterpolateHeader(SoInterpolateVec4f, SoMFVec4f)
#include <Inventor/engines/SoInterpolateAbs.h>
#include <Inventor/fields/SoMFVec4f.h>

class SoInterpolateVec4f : public SoInterpolate {
  typedef SoInterpolate inherited;
  SO_ENGINE_HEADER(SoInterpolateVec4f);

public:
  SoMFVec4f input0;
  SoMFVec4f input1;

  SoInterpolateVec4f();

  static void initClass();

private:
  virtual ~SoInterpolateVec4f();
  virtual void evaluate();

};
//$ END TEMPLATE InterpolateHeader

#endif // !__SOINTERPOLATEVEC4F_H__

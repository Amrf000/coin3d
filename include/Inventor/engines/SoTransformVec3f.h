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

#ifndef COIN_SOTRANSFORMVEC3F_H
#define COIN_SOTRANSFORMVEC3F_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/engines/SoEngineOutput.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFMatrix.h>

class COIN_DLL_EXPORT SoTransformVec3f : public SoEngine {
  typedef SoEngine inherited;

  SO_ENGINE_HEADER(SoTransformVec3f);

public:

  SoMFVec3f vector;
  SoMFMatrix matrix;

  SoEngineOutput point;           // SoMFVec3f
  SoEngineOutput direction;       // SoMFVec3f
  SoEngineOutput normalDirection; // SoMFVec3f

  SoTransformVec3f(void);
  static void initClass(void);

protected:
  virtual ~SoTransformVec3f();

private:
  virtual void evaluate(void);
};

#endif // !COIN_SOTRANSFORMVEC3F_H

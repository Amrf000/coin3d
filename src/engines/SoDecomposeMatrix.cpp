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

/*!
  \class SoDecomposeMatrix SoDecomposeMatrix.h Inventor/engines/SoDecomposeMatrix.h
  \brief The SoDecomposeMatrix class is used to decompose a matrix into simple transformations.
  \ingroup engines

  FIXME: doc
*/

#include <Inventor/engines/SoDecomposeMatrix.h>
#include <Inventor/lists/SoEngineOutputList.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/engines/SoSubEngineP.h>

SO_ENGINE_SOURCE(SoDecomposeMatrix);

/*!
  Default constructor.
*/
SoDecomposeMatrix::SoDecomposeMatrix()
{
  SO_ENGINE_INTERNAL_CONSTRUCTOR(SoDecomposeMatrix);

  SO_ENGINE_ADD_INPUT(matrix,(SbMatrix()));
  SO_ENGINE_ADD_INPUT(center,(SbVec3f()));

  SO_ENGINE_ADD_OUTPUT(translation,SoMFVec3f);
  SO_ENGINE_ADD_OUTPUT(rotation,SoMFRotation);
  SO_ENGINE_ADD_OUTPUT(scaleFactor,SoMFVec3f);
  SO_ENGINE_ADD_OUTPUT(scaleOrientation,SoMFRotation);
}

// overloaded from parent
void
SoDecomposeMatrix::initClass()
{
  SO_ENGINE_INTERNAL_INIT_CLASS(SoDecomposeMatrix);
}

//
// private members
//
SoDecomposeMatrix::~SoDecomposeMatrix()
{
}

// overloaded from parent
void
SoDecomposeMatrix::evaluate()
{
  int num = this->matrix.getNum();

  SO_ENGINE_OUTPUT(translation,SoMFVec3f,setNum(num));
  SO_ENGINE_OUTPUT(rotation,SoMFRotation,setNum(num));
  SO_ENGINE_OUTPUT(scaleFactor,SoMFVec3f,setNum(num));
  SO_ENGINE_OUTPUT(scaleOrientation,SoMFRotation,setNum(num));

  int i;
  SbVec3f translationVal,scaleFactorVal;
  SbRotation rotationVal,scaleOrientationVal;
  for (i = 0; i < num; i++) {
    SbVec3f c = (i < center.getNum()) ? center[i] : SbVec3f(0.0f, 0.0f, 0.0f);
    this->matrix[i].getTransform(translationVal,rotationVal,scaleFactorVal,
                                 scaleOrientationVal, c);
    SO_ENGINE_OUTPUT(translation,SoMFVec3f,set1Value(i,translationVal));
    SO_ENGINE_OUTPUT(rotation,SoMFRotation,set1Value(i,rotationVal));
    SO_ENGINE_OUTPUT(scaleFactor,SoMFVec3f,set1Value(i,scaleFactorVal));
    SO_ENGINE_OUTPUT(scaleOrientation,SoMFRotation,
                     set1Value(i,scaleOrientationVal));
  }
}

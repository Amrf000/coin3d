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

#ifndef _SO_GET_MATRIX_ACTION_H_
#define _SO_GET_MATRIX_ACTION_H_

#include <Inventor/confdep.h>
#if defined(COIN_EXCLUDE_SOGETMATRIXACTION)
#error "This file is excluded from Coin through the configuration system!"
#endif // COIN_EXCLUDE_SOGETMATRIXACTION

#include <Inventor/actions/SoAction.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbRotation.h>

#ifdef __SOLIB_INTERNAL__
#include <Inventor/SbMatrix.h>
#include <Inventor/SbVec3f.h>
#else // !__SOLIB_INTERNAL__
#include <Inventor/SbLinear.h>
#endif // !__SOLIB_INTERNAL__

class SoGetMatrixAction : public SoAction {
  typedef SoAction inherited;

//$ BEGIN TEMPLATE ActionHeader( SoGetMatrixAction )
private:
  static SoType classTypeId;

public:
  virtual SoType getTypeId(void) const;
  static SoType getClassTypeId(void);

protected:
  virtual const SoEnabledElementsList & getEnabledElements(void) const;
  static SoEnabledElementsList * enabledElements;
  static SoActionMethodList * methods;

public:
  static void addMethod(const SoType type, SoActionMethod method);
  static void enableElement(const SoType type, const int stackIndex);

  static void initClass(void);
  static void cleanClass(void);

  virtual ~SoGetMatrixAction();
//$ END TEMPLATE ActionHeader

public:

  SoGetMatrixAction(const SbViewportRegion &newRegion);

  void setViewportRegion(const SbViewportRegion &newRegion);
  const SbViewportRegion &getViewportRegion() const;

  SbMatrix & getMatrix(void);
  SbMatrix & getInverse(void);
  SbMatrix & getTextureMatrix(void);
  SbMatrix & getTextureInverse(void);

  // these four functions are not in the original Inventor API
  //FIXME: Remove og tag them as non-standard in some way? (kintel 19990615)
  void mult(const SbMatrix &matrix);
  void translateBy(const SbVec3f &vec);
  void rotateBy(const SbRotation &rot);
  void scaleBy(const SbVec3f &scaleFactor);

protected:
  virtual void beginTraversal(SoNode *node);
  
private:
  SbMatrix matrix;
  SbMatrix invMatrix;
  SbMatrix texMatrix;
  SbMatrix invTexMatrix;
  SbViewportRegion viewportRegion;
}; // class SoGetMatrixAction

#endif // ! _SO_GET_MATRIX_ACTION_H_

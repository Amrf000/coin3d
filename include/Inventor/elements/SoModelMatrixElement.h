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

#ifndef COIN_SOMODELMATRIXELEMENT_H
#define COIN_SOMODELMATRIXELEMENT_H

#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/SbMatrix.h>
#include <Inventor/lists/SbPList.h>


class SoModelMatrixElement : public SoAccumulatedElement {
  typedef SoAccumulatedElement inherited;

  SO_ELEMENT_HEADER(SoModelMatrixElement);
public:
  static void initClass(void);
protected:
  virtual ~SoModelMatrixElement();

public:
  virtual void init(SoState * state);
  virtual void push(SoState * state);
  virtual SbBool matches(const SoElement * element) const;
  static void makeIdentity(SoState * const state, SoNode * const node);
  static void set(SoState * const state, SoNode * const node,
                  const SbMatrix & matrix);
  static void setCullMatrix(SoState * state, SoNode * node,
                            const SbMatrix & matrix);
  static void mult(SoState * const state, SoNode * const node,
                   const SbMatrix & matrix);
  static void translateBy(SoState * const state, SoNode * const node,
                          const SbVec3f & translation);
  static void rotateBy(SoState * const state, SoNode * const node,
                       const SbRotation & rotation);
  static void scaleBy(SoState * const state, SoNode * const node,
                      const SbVec3f & scaleFactor);

  static SbMatrix pushMatrix(SoState * const state);
  static void popMatrix(SoState * const state, const SbMatrix & matrix);

  static const SbMatrix & getCombinedCullMatrix(SoState * const state);
  static const SbMatrix & get(SoState * const state);
  static const SbMatrix & get(SoState * const state, SbBool & isIdentity);
  static const SbMatrix & getInverse(SoState * const state);
  static const SbMatrix & getInverse(SoState * const state, SbBool & isIdentity);

protected:
  virtual void makeEltIdentity(void);
  virtual void setElt(const SbMatrix & matrix);
  virtual void multElt(const SbMatrix & matrix);
  virtual void translateEltBy(const SbVec3f & translation);
  virtual void rotateEltBy(const SbRotation & rotation);
  virtual void scaleEltBy(const SbVec3f & scaleFactor);
  virtual SbMatrix pushMatrixElt(void);
  virtual void popMatrixElt(const SbMatrix & matrix);

protected:
  SbMatrix modelMatrix;
  SbMatrix cullMatrix;
  SbMatrix combinedMatrix;
  uint32_t flags;

};

#endif // !COIN_SOMODELMATRIXELEMENT_H

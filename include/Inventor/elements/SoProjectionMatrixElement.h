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

#ifndef COIN_SOPROJECTIONMATRIXELEMENT_H
#define COIN_SOPROJECTIONMATRIXELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbMatrix.h>


class COIN_DLL_EXPORT SoProjectionMatrixElement : public SoReplacedElement {
  typedef SoReplacedElement inherited;

  SO_ELEMENT_HEADER(SoProjectionMatrixElement);
public:
  static void initClass(void);
protected:
  virtual ~SoProjectionMatrixElement();

public:
  virtual void init(SoState * state);

  static void set(SoState * const state, SoNode * const node,
                  const SbMatrix & matrix);
  static const SbMatrix &get(SoState * const state);

protected:
  SbMatrix projectionMatrix;
  virtual void setElt(SbMatrix const & matrix);

};

#endif // !COIN_SOPROJECTIONMATRIXELEMENT_H

#ifndef COIN_SOBBOXMODELMATRIXELEMENT_H
#define COIN_SOBBOXMODELMATRIXELEMENT_H

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

#include <Inventor/elements/SoModelMatrixElement.h>

class SoLocalBBoxMatrixElement;

class COIN_DLL_API SoBBoxModelMatrixElement : public SoModelMatrixElement {
  typedef SoModelMatrixElement inherited;

  SO_ELEMENT_HEADER(SoBBoxModelMatrixElement);
public:
  static void initClass(void);
protected:
  virtual ~SoBBoxModelMatrixElement();

public:
  virtual void init(SoState * state);

  virtual void push(SoState * state);

  static  void reset(SoState * const state, SoNode * const node);
  static  void pushMatrix(SoState * const state, SbMatrix & matrix,
                          SbMatrix & localmatrix);
  static  void popMatrix(SoState * const state, const SbMatrix & matrix,
                         const SbMatrix & localmatrix);

protected:
  virtual void makeEltIdentity(void);
  virtual void setElt(const SbMatrix & matrix);
  virtual void multElt(const SbMatrix & matrix);
  virtual void translateEltBy(const SbVec3f & translation);
  virtual void rotateEltBy(const SbRotation & translation);
  virtual void scaleEltBy(const SbVec3f & scaleFactor);

// the following two functions should not be called - only for debug usage
  virtual SbMatrix pushMatrixElt();
  virtual void popMatrixElt(const SbMatrix & matrix);

private:
  SoLocalBBoxMatrixElement *getLocal();

  SoState *state;
};

#endif // !COIN_SOBBOXMODELMATRIXELEMENT_H

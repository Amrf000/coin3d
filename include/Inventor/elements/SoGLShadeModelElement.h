#ifndef COIN_SOGLSHADEMODELELEMENT_H
#define COIN_SOGLSHADEMODELELEMENT_H

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

#include <Inventor/elements/SoSubElement.h>

class COIN_DLL_API SoGLShadeModelElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoGLShadeModelElement);
public:
  static void initClass(void);
protected:
  virtual ~SoGLShadeModelElement();

public:
  virtual void init(SoState * state);
  virtual void push(SoState * state);
  virtual void pop(SoState * state,
                   const SoElement * prevTopElement);

  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo() const;

  static void set(SoState * state, const SbBool flat);

  virtual void lazyEvaluate(void) const;
  virtual SbBool isLazy(void) const;
  static void forceSend(SoState * const state, const SbBool flat);

  static const SoGLShadeModelElement * getInstance(SoState * state);

private:
  SbBool flat;
  SbBool glflat;
  void updategl(const SbBool flatshade) const;
};

#endif // !COIN_SOGLSHADEMODELELEMENT_H

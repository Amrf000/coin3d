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

#ifndef COIN_SOGLCOLORINDEXELEMENT_H
#define COIN_SOGLCOLORINDEXELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>

class COIN_DLL_API SoGLColorIndexElement : public SoReplacedElement {
  typedef SoReplacedElement inherited;

  SO_ELEMENT_HEADER(SoGLColorIndexElement);
public:
  static void initClass(void);
protected:
  virtual ~SoGLColorIndexElement();

public:
  static SbBool isColorIndexMode(SoState * state);

  virtual void init(SoState * state);
  virtual void push(SoState * state);

  static void set(SoState * const state, SoNode * const node,
                  const int32_t numindices, const int32_t * const indices);

  static const SoGLColorIndexElement * getInstance(SoState *state);

  int32_t getNum(void) const;
  void send(const int index);

private:
  int numindices;
  const int32_t * indices;
  SbBool colorindexmode;
};

#endif // !COIN_SOGLCOLORINDEXELEMENT_H

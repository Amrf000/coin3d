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

#ifndef COIN_SOCULLELEMENT_H
#define COIN_SOCULLELEMENT_H

#include <Inventor/elements/SoSubElement.h>
#include <Inventor/SbPlane.h>

class SbBox3f;
class SbViewVolume;

class COIN_DLL_API SoCullElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoCullElement);
public:
  static void initClass(void);
protected:
  virtual ~SoCullElement();

public:

  virtual void init(SoState * state);
  virtual void push(SoState * state);
  
  static void setViewVolume(SoState * state, const SbViewVolume & vv);
  static void addPlane(SoState * state, const SbPlane & newplane);
  static SbBool cullBox(SoState * state, const SbBox3f & box, const SbBool transform = TRUE);
  static SbBool cullTest(SoState * state, const SbBox3f & box, const SbBool transform = TRUE);
  static SbBool completelyInside(SoState * state);

  virtual SbBool matches(const SoElement * elt) const;
  virtual SoElement * copyMatchInfo(void) const;

private:

  enum { MAXPLANES = 32 };

  static SbBool docull(SoState * state, const SbBox3f & box, const SbBool transform,
                       const SbBool updateelem);

  SbPlane plane[MAXPLANES];
  int numplanes;
  unsigned int flags;
  int vvindex;
};

#endif // !COIN_SOCULLELEMENT_H

#ifndef COIN_SOTEXTURECOORDINATEBINDINGELEMENT_H
#define COIN_SOTEXTURECOORDINATEBINDINGELEMENT_H

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

#include <Inventor/elements/SoInt32Element.h>

class COIN_DLL_API SoTextureCoordinateBindingElement : public SoInt32Element {
  typedef SoInt32Element inherited;

  SO_ELEMENT_HEADER(SoTextureCoordinateBindingElement);
public:
  static void initClass(void);
protected:
  virtual ~SoTextureCoordinateBindingElement();

public:
// constants: (numbers are adjusted for Inventor 2.0 binary format files)
  enum Binding {
    PER_VERTEX = 2,
    PER_VERTEX_INDEXED = 3
  };

  virtual void init(SoState * state);

  static void set(SoState * const state, SoNode * const node,
                  const Binding binding);
  static void set(SoState * const state, const Binding binding);

  static Binding get(SoState * const state);

  static Binding getDefault(void);
};

#endif // !COIN_SOTEXTURECOORDINATEBINDINGELEMENT_H

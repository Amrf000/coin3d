#ifndef COIN_SOINT32ELEMENT_H
#define COIN_SOINT32ELEMENT_H

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
#include <Inventor/system/inttypes.h>

class COIN_DLL_API SoInt32Element : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_ABSTRACT_HEADER(SoInt32Element);
public:
  static void initClass(void);
protected:
  virtual ~SoInt32Element();

public: // constructor / destructor / etc.
  virtual void init(SoState * state);

  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  virtual void print(FILE * file) const;

  static  void set(const int index, SoState * const state,
                    SoNode * const node, const int32_t value);
  static  void set(const int index, SoState * const state,
                    const int32_t value);
  static  int32_t get(const int index, SoState * const state);
  virtual void setElt(int32_t value);

protected:
  int32_t data;

};

#endif // !COIN_SOINT32ELEMENT_H

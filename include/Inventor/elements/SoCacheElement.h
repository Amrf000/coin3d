#ifndef COIN_SOCACHEELEMENT_H
#define COIN_SOCACHEELEMENT_H

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

class SoCache;

class COIN_DLL_API SoCacheElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoCacheElement);
public:
  static void initClass(void);
protected:
  virtual ~SoCacheElement();

public:
  virtual void init(SoState * state);

  virtual void push(SoState * state);
  virtual void pop(SoState * state, const SoElement * prevTopElement);

  static void set(SoState * const state, SoCache * const cache);
  SoCache * getCache(void) const;
  static SbBool anyOpen(SoState * const state);
  static void invalidate(SoState * const state);
  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;
  SoCacheElement * getNextCacheElement(void) const;

  static void addElement(SoState * const state,
                         const SoElement * const element);
  static void addCacheDependency(SoState * const state, SoCache * const cache);
  static SbBool setInvalid(const SbBool newvalue);
  static SoCache * getCurrentCache(SoState * const state);

private:
  SoCache * cache;
  static SbBool invalidated;
};

#endif // !COIN_SOCACHEELEMENT_H

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

#ifndef COIN_SOPROTOELEMENT_H
#define COIN_SOPROTOELEMENT_H

#include <Inventor/elements/SoSubElement.h>

class COIN_DLL_EXPORT SoPROTOElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoPROTOElement);
public:
  static void initClass(void);
protected:
  virtual ~SoPROTOElement();

public:
  virtual void init(SoState * state);

  virtual void push(SoState * state);
  virtual void pop(SoState * state,
              const SoElement * prevTopElement);

  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  // FIXME: quick hack. 19980810 mortene.
  class SoPROTO *nodeptr;
  // larsa: SoElement got dataNode member for this :(
  // - might fix this later
};

#endif // !COIN_SOPROTOELEMENT_H

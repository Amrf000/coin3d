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

#ifndef COIN_SODECIMATIONTYPEELEMENT_H
#define COIN_SODECIMATIONTYPEELEMENT_H

#include <Inventor/elements/SoInt32Element.h>


class COIN_DLL_EXPORT SoDecimationTypeElement : public SoInt32Element {
  typedef SoInt32Element inherited;

  SO_ELEMENT_HEADER(SoDecimationTypeElement);
public:
  static void initClass(void);
protected:
  virtual ~SoDecimationTypeElement();

public:
  enum Type { AUTOMATIC, HIGHEST, LOWEST, PERCENTAGE };

  virtual void init(SoState * state);

  static  void set(SoState * const state, const Type type);
  static  void set(SoState * const state, SoNode * const node, const Type type);

  static Type get(SoState * const state);
  static Type getDefault(void);

  virtual void print(FILE *fp) const;

};

#endif // !COIN_SODECIMATIONTYPEELEMENT_H

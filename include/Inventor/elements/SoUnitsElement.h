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

#ifndef COIN_SOUNITSELEMENT_H
#define COIN_SOUNITSELEMENT_H

#include <Inventor/elements/SoInt32Element.h>


class COIN_DLL_EXPORT SoUnitsElement : public SoInt32Element {
  typedef SoInt32Element inherited;

  SO_ELEMENT_HEADER(SoUnitsElement);
public:
  static void initClass(void);
protected:
  virtual ~SoUnitsElement();

public:
// constants:
  enum Units {
    // We have to start at 0, or code in nodes/SoUnits.cpp will crash
    // and burn. --mortene
    METERS = 0,
    CENTIMETERS,
    MILLIMETERS,
    MICROMETERS,
    MICRONS,
    NANOMETERS,
    ANGSTROMS,
    KILOMETERS,
    FEET,
    INCHES,
    POINTS,
    YARDS,
    MILES,
    NAUTICAL_MILES
  };

  virtual void init(SoState * state);

  static  void set(SoState * const state, SoNode * const node,
                   const Units units);
  static  void set(SoState * const state, const Units units);
  static Units get(SoState * const state);
  static Units getDefault();

};

#endif // !COIN_SOUNITSELEMENT_H

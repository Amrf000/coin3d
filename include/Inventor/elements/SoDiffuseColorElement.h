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

#ifndef COIN_SODIFFUSECOLORELEMENT_H
#define COIN_SODIFFUSECOLORELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>

class SbColor;


class COIN_DLL_EXPORT SoDiffuseColorElement : public SoReplacedElement {
  typedef SoReplacedElement inherited;

  SO_ELEMENT_HEADER(SoDiffuseColorElement);
public:
  static void initClass(void);
protected:
  virtual ~SoDiffuseColorElement();

public:
  virtual void init(SoState * state);

  static void set(SoState * const state, SoNode * const node,
                  const int32_t numColors, const SbColor * const colors);

  static void set(SoState * const state, SoNode * const node,
                  const int32_t numColors, const uint32_t * const colors,
                  const SbBool packedtransparency = FALSE);

  static const SoDiffuseColorElement * getInstance(SoState *state);

  int32_t getNum(void) const;
  const SbColor &get(const int index) const;

  SbBool isPacked(void) const;
  SbBool hasPackedTransparency(void) const;

  const SbColor *getColorArrayPtr() const;
  const uint32_t *getPackedArrayPtr() const;

protected:
  friend class SoMaterialBundle;
  virtual void setElt(const int32_t numColors, const SbColor * const colors);
  virtual void setElt(const int32_t numColors,
                      const uint32_t * const packedcolors,
                      const SbBool packedtransparency);

  int numColors;
  const SbColor *colors;
  const uint32_t *packedColors;
  SbBool packedTransparency;
};

#endif // !COIN_SODIFFUSECOLORELEMENT_H

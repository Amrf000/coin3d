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

#ifndef COIN_SOANNOTEXT3RENDERPRINTELEMENT_H
#define COIN_SOANNOTEXT3RENDERPRINTELEMENT_H

#include <Inventor/elements/SoInt32Element.h>


class COIN_DLL_EXPORT SoAnnoText3RenderPrintElement : public SoInt32Element {
  typedef SoInt32Element inherited;

  SO_ELEMENT_HEADER(SoAnnoText3RenderPrintElement);
public:
  static void initClass(void);
protected:
  virtual ~SoAnnoText3RenderPrintElement();

public:
  enum RenderPrintType {
    RENDER3D_PRINT_VECTOR, RENDER3D_PRINT_RASTER, RENDER2D_PRINT_RASTER
  };

  virtual void init(SoState * state);
  static void set(SoState * const state, const RenderPrintType hint);
  static RenderPrintType get(SoState * const state);
  static RenderPrintType getDefault(void);

  static void set(SoState * const state, SoNode * const node,
                  const RenderPrintType type);
};

#endif // !COIN_SOANNOTEXT3RENDERPRINTELEMENT_H

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

#ifndef COIN_SOGLLINEWIDTHELEMENT_H
#define COIN_SOGLLINEWIDTHELEMENT_H

#include <Inventor/elements/SoLineWidthElement.h>


class COIN_DLL_EXPORT SoGLLineWidthElement : public SoLineWidthElement {
  typedef SoLineWidthElement inherited;

  SO_ELEMENT_HEADER(SoGLLineWidthElement);
public:
  static void initClass(void);
protected:
  virtual ~SoGLLineWidthElement();

public:
  virtual void init(SoState * state);

  virtual void push(SoState * state);
  virtual void pop(SoState * state,
                   const SoElement * prevTopElement);
  void evaluate() const;

protected:
  virtual void setElt(float width);

private:
  static float sizerange[2];
  float current;
  void updategl();

};

#endif // !COIN_SOGLLINEWIDTHELEMENT_H

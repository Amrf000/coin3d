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

#ifndef COIN_SOSFIELD_H
#define COIN_SOSFIELD_H

#include <Inventor/fields/SoField.h>


class COIN_DLL_EXPORT SoSField : public SoField {
  typedef SoField inherited;

public:
  virtual ~SoSField();

  static void initClass(void);
  static SoType getClassTypeId(void);

protected:
  SoSField(void);

private:
  static SoType classTypeId;
};

#endif // !COIN_SOSFIELD_H

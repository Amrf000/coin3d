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

#ifndef COIN_SOMFVEC3F_H
#define COIN_SOMFVEC3F_H

#include <Inventor/fields/SoMField.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbVec3f.h>


class COIN_DLL_EXPORT SoMFVec3f : public SoMField {
  typedef SoMField inherited;

  SO_MFIELD_HEADER(SoMFVec3f, SbVec3f, const SbVec3f &);

public:
  static void initClass(void);

  void setValues(const int start, const int num, const float xyz[][3]);
  void set1Value(const int idx, const float x, const float y, const float z);
  void set1Value(const int idx, const float xyz[3]);
  void setValue(const float x, const float y, const float z);
  void setValue(const float xyz[3]);
};

#endif // !COIN_SOMFVEC3F_H

/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

#ifndef __SOVRMLINTERPOUTPUTLIST_H__
#define __SOVRMLINTERPOUTPUTLIST_H__

#include <Inventor/lists/SbPList.h>

class SoVRMLInterpOutput;

class SoVRMLInterpOutputList : public SbPList {
  typedef SbPList inherited;

public:
  SoVRMLInterpOutputList(void);
  SoVRMLInterpOutputList(const int size);
  SoVRMLInterpOutputList(const SoVRMLInterpOutputList & l);
  ~SoVRMLInterpOutputList(void);

  void append(SoVRMLInterpOutput * const ptr);
  void insert(SoVRMLInterpOutput * const ptr, const int addBefore);
  void set(const int i, SoVRMLInterpOutput * const ptr);
  SoVRMLInterpOutput * operator [](const int i) const;
};

#endif // !__SOVRMLINTERPOUTPUTLIST_H__

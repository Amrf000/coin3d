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

#ifndef COIN_SOLINEDETAIL_H
#define COIN_SOLINEDETAIL_H

#include <Inventor/details/SoPointDetail.h>


class COIN_DLL_EXPORT SoLineDetail : public SoDetail {
  typedef SoDetail inherited;

  SO_DETAIL_HEADER(SoLineDetail);

public:
  SoLineDetail(void);
  virtual ~SoLineDetail();

  static void initClass(void);
  virtual SoDetail * copy(void) const;

  const SoPointDetail * getPoint0(void) const;
  const SoPointDetail * getPoint1(void) const;

  int getLineIndex(void) const;
  int getPartIndex(void) const;

  void setPoint0(const SoPointDetail * const detail);
  void setPoint1(const SoPointDetail * const detail);
  void setLineIndex(const int idx);
  void setPartIndex(const int idx);

  void incLineIndex(void);
  void incPartIndex(void);

private:
  SoPointDetail points[2];
  int lineindex;
  int partindex;
};

#endif // COIN_SOLINEDETAIL_H

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

#ifndef COIN_LISTS_SOCALLBACKLIST_H
#define COIN_LISTS_SOCALLBACKLIST_H

// NB: make sure the ifdef-test above wrapping this includefile is
// _not_ checking on and setting the same define-string as the other
// SoCallbackList.h file in misc/.

#include <Inventor/lists/SbPList.h>

typedef void SoCallbackListCB(void * userdata, void * callbackdata);


class COIN_DLL_EXPORT SoCallbackList {
public:
  SoCallbackList(void);
  ~SoCallbackList();

  void addCallback(SoCallbackListCB * f, void * userData = NULL);
  void removeCallback(SoCallbackListCB * f, void * userdata = NULL);

  void clearCallbacks(void);
  int getNumCallbacks(void) const;

  void invokeCallbacks(void * callbackdata);

private:
  SbList<SoCallbackListCB *> funclist;
  SbPList datalist;
};

#endif // !COIN_LISTS_SOCALLBACKLIST_H

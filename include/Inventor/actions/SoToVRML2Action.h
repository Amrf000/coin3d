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

#ifndef COIN_SOTOVRML2ACTION_H
#define COIN_SOTOVRML2ACTION_H

#include <Inventor/actions/SoToVRMLAction.h>


class COIN_DLL_EXPORT SoToVRML2Action : public SoToVRMLAction {
  typedef SoToVRMLAction inherited;

  SO_ACTION_HEADER(SoToVRML2Action);

public:
  SoToVRML2Action(void);
  virtual ~SoToVRML2Action();

  static void initClass(void);

protected:
  virtual void beginTraversal(SoNode * node);
};

#endif // !COIN_SOTOVRML2ACTION_H

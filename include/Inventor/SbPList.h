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

#ifndef COIN_SBPLIST_H
#define COIN_SBPLIST_H

#ifndef COIN_INTERNAL
 // The next two includes are for Open Inventor compatibility.
 #include <Inventor/SbBasic.h>
 #include <Inventor/SbLinear.h>
 // Here's the class definition of SbPList in Coin.
 #include <Inventor/lists/SbPList.h>
#else // COIN_INTERNAL
 #error "Do not include Inventor/SbPList.h internally (use Inventor/lists/SbPList.h)."
#endif // COIN_INTERNAL

#endif // !COIN_SBPLIST_H

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

#ifndef COIN_SOAPPEARANCEKIT_H
#define COIN_SOAPPEARANCEKIT_H

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoBaseKit.h>


class COIN_DLL_EXPORT SoAppearanceKit : public SoBaseKit {
  typedef SoBaseKit inherited;

  SO_KIT_HEADER(SoAppearanceKit);

  SO_KIT_CATALOG_ENTRY_HEADER(complexity);
  SO_KIT_CATALOG_ENTRY_HEADER(drawStyle);
  SO_KIT_CATALOG_ENTRY_HEADER(environment);
  SO_KIT_CATALOG_ENTRY_HEADER(font);
  SO_KIT_CATALOG_ENTRY_HEADER(lightModel);
  SO_KIT_CATALOG_ENTRY_HEADER(material);
  SO_KIT_CATALOG_ENTRY_HEADER(texture2);

public:
  SoAppearanceKit(void);

  static void initClass(void);

protected:
  virtual ~SoAppearanceKit();
};

#endif // !COIN_SOAPPEARANCEKIT_H

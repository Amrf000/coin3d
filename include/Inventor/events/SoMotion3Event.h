/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use Coin with software that is incompatible
 *  licensewise with the GPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef COIN_SOMOTION3EVENT_H
#define COIN_SOMOTION3EVENT_H

#include <Inventor/events/SoSubEvent.h>
#include <Inventor/SbVec3f.h>
#include <Inventor/SbRotation.h>


class COIN_DLL_API SoMotion3Event : public SoEvent {
  typedef SoEvent inherited;

  SO_EVENT_HEADER();

public:
  SoMotion3Event(void);
  virtual ~SoMotion3Event();

  void setTranslation(const SbVec3f & t);
  const SbVec3f & getTranslation(void) const;

  void setRotation(const SbRotation & r);
  const SbRotation & getRotation(void) const;

  static void initClass(void);

private:
  SbVec3f translation;
  SbRotation rotation;
};

#endif // !COIN_SOMOTION3EVENT_H

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

#ifndef COIN_SOBOUNDINGBOXCACHE_H
#define COIN_SOBOUNDINGBOXCACHE_H

#include <Inventor/caches/SoCache.h>
#include <Inventor/SbXfBox3f.h>

class COIN_DLL_API SoBoundingBoxCache : public SoCache {
  typedef SoCache inherited;
public:
  SoBoundingBoxCache(SoState *state);
  ~SoBoundingBoxCache();

  void set(const SbXfBox3f &boundingBox,
           SbBool centerSet,
           const SbVec3f &centerPoint);

  const SbXfBox3f &getBox() const;
  const SbBox3f &getProjectedBox() const;

  SbBool isCenterSet() const;
  const SbVec3f &getCenter() const;

  static void setHasLinesOrPoints(SoState *state);
  SbBool hasLinesOrPoints() const;

private:
  SbXfBox3f bbox;
  SbBox3f localBBox;
  SbVec3f centerPoint;
  unsigned int centerSet : 1;
  unsigned int linesOrPoints : 1;
};

#endif // !COIN_SOBOUNDINGBOXCACHE_H

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

#ifndef COIN_SOSEARCHACTION_H
#define COIN_SOSEARCHACTION_H

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/SbName.h>
#include <Inventor/lists/SoPathList.h>


class COIN_DLL_API SoSearchAction : public SoAction {
  typedef SoAction inherited;

  SO_ACTION_HEADER(SoSearchAction);

public:
  SoSearchAction(void);
  virtual ~SoSearchAction();

  static void initClass(void);

  enum LookFor { NODE = 1, TYPE = 2, NAME = 4 };
  enum Interest { FIRST, LAST, ALL };

  void setNode(SoNode * const node);
  SoNode * getNode(void) const;
  void setType(const SoType type, const SbBool chkderived = TRUE);
  SoType getType(SbBool & chkderived) const;
  void setName(const SbName name);
  SbName getName(void) const;
  void setFind(const int what);
  int getFind(void) const;
  void setInterest(const Interest interest);
  Interest getInterest(void) const;
  void setSearchingAll(const SbBool searchall);
  SbBool isSearchingAll(void) const;
  SoPath * getPath(void) const;
  SoPathList & getPaths(void);
  void reset(void);

  void setFound(void);
  SbBool isFound(void) const;
  void addPath(SoPath * const path);

protected:
  virtual void beginTraversal(SoNode * node);

private:
  int lookfor;
  Interest interest;
  SbBool searchall, chkderived;
  SoNode * node;
  SoType type;
  SbName name;
  SoPath * path;
  SoPathList paths;
};

#endif // !COIN_SOSEARCHACTION_H
